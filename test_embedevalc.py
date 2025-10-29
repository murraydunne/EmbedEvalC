import subprocess
import os
import json
import sys
import glob

start_offset = 0
stop_offset = 46
verbose = False
cannonical = False
single = False
short_test = False

if len(sys.argv) <= 1 or sys.argv[1] == 'help' or sys.argv[1] == '-help' or sys.argv[1] == '--help':
    print("""
Usage:
    python3 test_embedevalc.py [path_to_llm_generated_code] [-v]
          
    IMPORTANT: you must download HumanEvalPlus.jsonl from EvalPlus and include it in the same directory as this file.
          
    The path to the LLM generated code should be a directory structured as follows (where [n] is the number of trials generated for each LLM):
          
        path_to_llm_generated_code/
            0/
                0.c
                1.c
                ...
                [n].c
            1/
                0.c
                1.c
                ...
                [n].c
            ...
            45/
                0.c
                1.c
                ...
                [n].c
        
    The -v option turns on verbose mode.
""")
    exit()

runpath = sys.argv[1]

for i in range(1, len(sys.argv)):
    if sys.argv[i] == '-v':
        verbose = True

testing_string = """
#include <stdio.h>
#include <string.h>
static int ___test_pass_count = 0;
void ___assert_function(int sum, const char* text) {
    ___test_pass_count += sum;
    //if(sum == 0) {
    //    printf("Failed %s\\n", text);
    //}
}
#define assert(exp) ___assert_function(((exp)?1:0), "case: " #exp " ")

int main() {
"""

# starting from 26
humaneval_map = [5, 7, 27, 51, 65, 79, 89, 101, 117, 125, 1, 11, 49, 69, 93, 0, 103, 105, 109, 113]

hevalp = []
with open('HumanEvalPlus-Mini.jsonl', 'r') as f:
    for line in f.readlines():
        hevalp.append(json.loads(line))

def extract_testcases(case):
    exec('global ' + case['entry_point'] + '\n\n' + case['prompt'] + case['canonical_solution'])

    tests = case['base_input'] + case['plus_input']
    result = []
    for test in tests:
        result.append((test, globals()[case['entry_point']](*test)))

    return result

def fill_test_case(template, testcase):
    
    segments = template.split('###')
    result = ''

    for i in range(len(segments)):
        if i % 2 == 0:
            result += segments[i]
        else:
            type_code = segments[i][-1]
            fill_object = None
            name = None
            if segments[i][0] == '_':
                fill_object = testcase[1]
                name = 'answer'
            else:
                fill_object = testcase[0][int(segments[i][:-1])]
                name = 'param' + str(int(segments[i][:-1]))
            
            if type_code == 'A':         
                for num in fill_object:
                    if num > 2 ** 63 - 1 or num < -1 * (2 ** 63 - 1):
                        raise ValueError("Illegal test case for C.")

                result += ', '.join([str(x) for x in fill_object])
            elif type_code == 'L':
                if type(fill_object) == list or type(fill_object) == tuple:
                    result += str(len(fill_object))
                elif fill_object == '':
                    result += str(0)
                else:
                    result += str(1)
            elif type_code == 'I':
                if fill_object > 2 ** 63 - 1 or fill_object < -1 * (2 ** 63 - 1):
                    raise ValueError("Illegal test case for C.")

                result += str(int(fill_object))
            elif type_code == 'P': # literal of any kind, for multi-type return
                if type(fill_object) == list or type(fill_object) == tuple:
                    result += ', '.join([str(x) for x in fill_object])
                else:
                    result += str(fill_object)
            elif type_code == 'D': # double-precision floating point
                result += str(fill_object)
            elif type_code == 'S':
                result += '"' + repr(fill_object)[1:-1] + '"'
            elif type_code == 'J': # jagged array of strings
                if type(fill_object) == list or type(fill_object) == tuple:
                    result += 'char** ' + name + ' = malloc(' + str(len(fill_object)) + ' * sizeof(char*));\n'
                    for j in range(len(fill_object)):
                        result += name + '[' + str(j) + '] = strdup("' + repr(fill_object[j])[1:-1] + '");\n'
                else:
                    result += 'char** ' + name + ' = malloc(1 * sizeof(char*));\n'
                    result += name + '[0] = strdup("' + repr(str(fill_object))[1:-1] + '");\n'
            elif type_code == 'B':
                if fill_object:
                    result += 'true'
                else:
                    result += 'false'
            else:
                raise Error("Invalid type code " + type_code)

    if verbose:
        print("Testcase inputs:", testcase)
        print("Filled string:", result)
        print("")
    return result

def truncate_on_brace(code):
    depth = 1
    for i in range(len(code)):
        if code[i] == '{' and code[i-1] != '\'':
            depth += 1
        elif code[i] == '}' and code[i-1] != '\'':
            depth -= 1

            if depth == 0:
                return code[:i+1]
            
    
    return code

results = []
max_repeat_count = 0

for i in range(start_offset, stop_offset):
    
    problem_dir = runpath + str(i) + '/'

    repeat_count = len(list(glob.glob(problem_dir + '*.c')))
    if repeat_count > max_repeat_count:
        max_repeat_count = repeat_count

    case_results = []
    
    for j in range(repeat_count):

        source_filename = 'tests/' + str(i) + '.c'
        combined_source_filename = 'test_run_' + str(i) + '.c'
        binary_filename = 'test_bin_' + str(i) + '.c'

        if not os.path.isfile(source_filename):
            print("Missing original question file", source_filename)
            exit()

        full_answer = None
        with open(source_filename) as f:
            full_answer = f.read()

        if '//***' not in full_answer:
            print("Invalid answer file missing //***")
            exit()

        split_answer = full_answer.split('//***')

        llm_output = None
        llm_file = None

        # if cannonical:
        #     llm_output = split_answer[1]
        #     llm_file = source_filename
        # else:
        llm_file = problem_dir + str(j) + '.c'
        if not os.path.isfile(llm_file): 
            print("Missing LLM answer file for question", i, "answerfile", j)
            #exit()
            #print(',-3', end="")
            continue

        with open(llm_file) as f:

            llm_content = f.read()

            # if 'llama' in runpath: # llama specific formatting
            #     newline_index = llm_content.index('\n')
            #     second_newline_index = llm_content[newline_index+1:].index('\n') + newline_index + 1
            #     llm_content = llm_content[second_newline_index + len(split_answer[0]):]

            llm_output = truncate_on_brace(llm_content)

        test_count = 0

        try:
            with open(combined_source_filename, 'w') as f:
                f.write(split_answer[0] + llm_output)
                f.write(testing_string)

                if i < 26:
                    f.write(split_answer[2])
                    test_count = split_answer[2].count('assert(')
                elif i >= 26 and i < 46:
                    test_cases = extract_testcases(hevalp[humaneval_map[i-26]])
                    for test in test_cases: #for each case in inputs
                        try:
                            case_text = fill_test_case(split_answer[2], test)
                            f.write('{\n' + case_text + '\n}')
                            test_count += 1
                        except ValueError as e:
                            if verbose:
                                print(str(e), "This is likely due to extremely large integers. Skipping.")

                f.write("\nreturn ___test_pass_count; }")

        except IndexError:
            os.remove(combined_source_filename)
            if os.path.isfile(combined_source_filename):
                print("ERROR!", combined_source_filename, "should be deleted!")

            raise ValueError("Missing //*** somewhere in file")

        if j == 0:
            print("Running case:", i)

        warn_err_text = None
        try: #compile the resulting file
            proc = subprocess.run(args = ['gcc', '-o', binary_filename, combined_source_filename, '-lm', '-fdiagnostics-show-option'],
                capture_output = True, text=True)
            warn_err_text = proc.stderr
        except:
            pass
        
        os.remove(combined_source_filename)
        if os.path.isfile(combined_source_filename):
            print("ERROR!", combined_source_filename, "should be deleted!")
            break

        if not os.path.isfile(binary_filename):
            if verbose:
                print("Failed to compile case", j, "of test", i)
            #print(',-2', end="")
            case_results.append(0)
            continue

        run_proc = subprocess.run(args = ['timeout', '2', './' + binary_filename], capture_output = True, text=True) #run the binary and grab the return code
        return_code = run_proc.returncode

        os.remove(binary_filename) #remove the binary after running it to clean up

        if os.path.isfile(binary_filename):
            print("ERROR!", binary_filename, "should be deleted!")
            break

        if return_code < 0 or return_code == 124:
            #print("Failed to run case", source_filename + '.', "Return code:", return_code)
            if verbose:
                print("Failed to run case", j, "of test", i)
            case_results.append(0)
            continue

        if return_code > test_count:
            # they made another main or similar
            if verbose:
                print("Invalid code (perhaps redefined main?) in", j, "of test", i)
            case_results.append(0)
            continue

        if verbose:
            print("Case", str(i), "file", str(j), "passed", return_code, '/', test_count, "tests.")

        case_results.append(float(return_code) / test_count)

    results.append(case_results)

print()
print()
print()
print()

print('testcase,' + ','.join(['trial_' + str(i) for i in range(max_repeat_count)]))
for i in range(len(results)):
    print(str(i) + ',' + ','.join([str(j) for j in results[i]]))
            





    


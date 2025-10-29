import os

repeat_factor = 20 # number of invocations of LLM, used for sampling pass@k
llm_result_directory = 'some-llms-results/'

def invoke_LLM_here(code_prompt):

    # my_prompt_prefix = "Continue the C code given directly in a markdown code block. No prose, no explanation. Output only C code.\n\n"
    # prompt = my_prompt_prefix + code_prompt
    # result = invoke_my_llm(prompt)

    result = ""
    return result


for i in range(46):

    source_filename = 'tests/' + str(i) + '.c'
    result_directory = llm_result_directory + str(i) + '/'

    os.makedirs(result_directory, exist_ok=True)

    if not os.path.isfile(source_filename):
        print("Missing", source_filename)
        continue

    full_answer = None
    with open(source_filename) as f:
        full_answer = f.read()

    if '//***' not in full_answer:
        print("Incomplete", source_filename)
        continue

    split_answer = full_answer.split('//***')
    prompt = split_answer[0]

    for j in range(repeat_factor):

        result_file = result_directory + str(j) + '.c'

        if os.path.isfile(result_file):
            print(result_file, "already exists. Skipping.")
            continue

        answer = invoke_LLM_here(prompt)

        with open(result_file, 'w') as f:
            f.write(answer)

        print("Completed question", i, "trial", j)





    


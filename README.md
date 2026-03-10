# EmbedEvalC
EmbedEvalC is a dataset for evaluating LLM C code generation. It contains test cases from open source projects (specifically [OpenSSL](https://github.com/openssl/openssl)), hand designed parsing challenges from network standards, and modified problems from [EvalPlus](https://github.com/evalplus/evalplus). Specifically EvalPlus's [HumanEvalPlus](https://github.com/evalplus/humanevalplus_release) dataset.

## Contributors

Contributors: Murray Dunne, Kylee Schram, Sebastian Fischmeister.

## Usage

To generate code with an LLM using the EmbedEvalC dataset, first ensure you have GCC installed, and then download HumanEvalPlus-Mini.jsonl from EvalPlus and place it in the current directory.

Then add the invocation of your LLM to `generate_embedevalc.py`. For example, you might alter it as follows:

```Python
def invoke_LLM_here(code_prompt):

    my_prompt_prefix = "Continue the C code given directly in a markdown code block. " +\
        "No prose, no explanation. Output only C code.\n\n"
    prompt = my_prompt_prefix + code_prompt
    result = invoke_my_llm(prompt)

    return result
```
You may also wish to adjust the directory constant defined in that file as follows:
```Python
llm_result_directory = 'some-llms-results/'
```
Once you have made your changes, run the `generate_embedevalc.py` file (in the directory this README file is in) to run the LLM against the EmbedEvalC dataset.

Once the script has finished running, you will be left with generated code in a directory structure as follows:
```
some-llms-results/
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
```

To generate a `.csv` of the test results for each run **ENSURE YOU ARE IN A CONTAINERIZED OR OTHER RESTRICTED/JAILED ENVIRONMENT** and then run `test_embedevalc.py some-llms-results/ > your-result-file.csv` in the same directory as this README file. It is dangerous to run untrusted generated C code in your regular working environment.

## Changes

All these projects are licensed under Apache-2.0, as is this project. Files incorporating changed content state their origin and "changes made" in the HUMAN NOTES section.

Significant changes were made to the original HumanEvalPlus code to translate it into the C language. We followed the following process when translating the problems:

We modified the HumanEvalPlus prompts from EvalPlus as follows to match the style used when writing our own and to adapt them to C conventions:
- Added a C-style function prototype consisting of function name and expected input parameters. Additional parameters of input length, for cases requiring an array input, and a pointer to store function results at were added where necessary according to C convention.
- In cases where expected output was an array, we explicitly instructed the LLM to return the length of the array and to place the resulting array at the double pointer indicated in the result parameter. 
- Explicitly instructed the LLM to begin completing code after the provided declaration
- Substituted types according to the mapping below.

We translated the HumanEvalPlus prompts from EvalPlus problems into handwritten in C according to the following rules:
- Do not consult LLMs at any point. This is intended to avoid threats to validity from using LLMs.
- Python ints become ints, floats become doubles, strings become const char* if input and char* otherwise. long longs may be needed for very large integers. 
- Keep sorting simple. Use bubble sort when sorting is needed.
- If an array needs to be returned, allocate it with malloc, put the pointer in a double-pointer parameter and return the length. Assume the caller will free it, but this should be indicated in a comment. 
- Two-dimensional arrays of fixed size should be done in a single allocation call malloc(n*m)
- Jagged arrays should be allocated using nested malloc calls.
- If an array is a parameter, add an integer length (or multiple lengths) parameter immediately after the array parameter.
- Use only standard library includes. This is done to provide consistency of imports across prompts and eliminate dependence on specialized libraries.
- Avoid stdio unless sprintf is an efficient solution for task completion.
- All other external necessary functions should be declared and defined in the prelude before the comment and the function header.
- Leave the original comment describing the function as intact as possible. Only modify it as necessary to express the problem in C, and keep any given examples in the comment.
- Unicode is not a part of the testing objective (we are using char*) and Unicode tests will auto-pass. They are not counted. 

For the OpenSSL open source challenges, we made modifications to the functions such that they better fit the above described format.

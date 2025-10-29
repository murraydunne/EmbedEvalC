# EmbedEvalC
EmbedEvalC is a dataset for evaluating LLM C code generation. It contains test cases from open source projects (specifically [OpenSSL](https://github.com/openssl/openssl)), hand designed parsing challenges from network standards, and modified problems from [EvalPlus](https://github.com/evalplus/evalplus). Specifically EvalPlus's [HumanEvalPlus](https://github.com/evalplus/humanevalplus_release) dataset.

## Contributors

Contributors include Murray Dunne and two others. Thier names will be added here pending their consent to posting their names.

## Usage

To generate code with an LLM using the EmbedEvalC dataset, first add the invocation of your LLM to `generate_embedevalc.py`, then run it.

To test that generated code, run `test_embedevalc.py` in a containerized or other jailed environment for safety and security.

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

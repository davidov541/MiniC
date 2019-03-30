#pragma once

// String Maximums
#define REG_LENGTH_MAX 4
#define LABEL_LENGTH_MAX 6
#define FUNC_LENGTH_MAX 100
#define ERROR_LENGTH_MAX 100
#define NUM_LENGTH_MAX 12
#define LINE_LENGTH_MAX 300
#define MAX_PREPROCESS_SIZE 20
#define NUMSREGS 2

// Errno Values
#define EOK 0
#define EHS 81
#define EN 82

// Compiler Flags
#define HELP L"-h"
#define HELPLONG L"--help"
#define VERSION L"-v"
#define COEOUTPUT L"-o"
#define NOASSEMBLE L"-c"
#define DEBUG L"-d"
#define ASSEMBLEONLY L"-a"
#define SDCARDOUT L"-s"
#define BOOTLOADER L"-b"

// Output Constants
#define VERSION_NO L"0.5"
#define VERSION_NUMBER_LABEL L"MiniC -- Version "

// Debug Output Constants
#define PREPROCESSING L"Preprocessing...\n"
#define SCANNING L"Scanning and Parsing...\n"
#define GATHERING_FUNCTIONS L"Gathering Relevant Functions\n"
#define TYPECHECKING L"Typechecking...\n"

// Error Handling Strings
#define MAX_ERROR_LEN 1000

//Unit Test Errors
#define NO_C_FILES L"ERROR: Failure to find any C files in directory to use. Check that they are present and have the .c suffix.\n"

// Input Errors
#define NO_TASK_INDICATED L"ERROR: No flag was given to indicate which task the compiler should take.\n"
#define NO_OUTPUT_INDICATED L"ERROR: No flag was given to indicate where the resulting code should be output.\n"
#define INVALID_INPUT_FILE L"ERROR: Could not open file %s for writing. Error Code - %d\n"
#define NO_DEBUG_CODE L"ERROR: Please indicate which debug flags you want included.\n"

// Compiling Errors
#define INVALID_PREPROCESSOR L"Invalid Preprocessor Directive %s\n"
#define INVALID_INCLUDE L"Invalid Include Statement %s\n"
#define CIRCULAR_REFERENCE L"Circular Reference detected involving %s\n"
#define INCLUDE_NOT_FOUND L"File %s was not found in the current directory, or was not able to be opened.\n"
#define FUNCTION_SIGNATURE_NOT_FOUND L"Function %s was not found.\n"

// Unit Test Constant Strings
#define OVERALL_START L"Starting Unit Test of Compiler in working directory \n%s...\n"
#define PROCESS_START L"Testing Compilation...\n"
#define PROCESS_RESULTS L"Input: %-38sError Code: %-15dError: %d\n"
#define PROCESS_CONCL L"Done Testing ProcessInstruction With %d Errors.\n"
#define OVERALL_CONCL L"All Testing Finished with %d Errors.\n"
#define PASS L"PASS"
#define FAIL L"FAIL"

// Wide Character Functions
#define fwopen _tfopen_s
#define wtoi _wtoi
#define getws _getws
#define wsystem _wsystem

// MISC.
#define TMP_FILE L"tmp"
#define ASM_TMP_FILE L"asmtmp"
#define PARSE_FILE "DebugParse.txt"
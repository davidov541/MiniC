#ifndef __BITEPICNESS_ASSEMBLER_CONSTANTS
#define __BITEPICNESS_ASSEMBLER_CONSTANTS

// NOTE: All sizes are +1 from actual, since the null terminator must be taken into account.

// Constants for Bit Sizes in Byte Code
#define B_FUNC_LEN 4
#define B_REG_LEN 6
#define B_C0REG_LEN 5
#define B_OP_LEN 6
#define B_IMM_LEN 8
#define B_TARGET_LEN 11
#define B_INSTRUCTION_LEN 17
#define B_MAX_WORDS_PER_INSTRUCTION 5
#define B_HEADER_LENGTH 62
#define B_CODE_SIZE (B_INSTRUCTION_LEN + 2)*B_MAX_WORDS_PER_INSTRUCTION*(numInstructions + numData) + 1 + B_HEADER_LENGTH

// Maximums for Assembly Code Strings
#define OP_LEN 5
#define REG_LEN 8
#define MAX_INST_STR_LEN 200
#define MAX_LABEL_LEN 100
#define MAX_IMM_DIGITS 3
#define MAX_INSTS_PER_INSTRUCTION 7

// Processor Dimensions
#define REGS_LEN 16
#define C0REGS_LEN 6
#define OPS_LEN 25
#define J_OPS_LEN 2
#define R_OPS_LEN 8
#define I_OPS_LEN 3
#define M_OPS_LEN 10
#define L_OPS_LEN 2
#define SYSI_OPS_LEN 2
#define SYSN_OPS_LEN 2
#define SYSR_OPS_LEN 2
#define SYSRR_OPS_LEN 2

// errno Extentions
#define EOK 0
#define OPERR 1
#define EHS 81
#define EN 82

// Error Handling
#define MAX_ERROR 100 + FILENAME_MAX
#define MAX_NUM_ERRORS 1000
#define INVALID_REG L"ERROR - Invalid Register %s located in instruction %d.\n"
#define INVALID_OP L"ERROR - Invalid Operation %s located in instruction %d.\n"
#define INVALID_OP_TYPE L"ERROR - Invalid Operation Type located in instruction %d.\n"
#define INVALID_LABEL L"ERROR - Invalid Label %s located in instruction %d.\n"
#define INVALID_PORT_NO L"ERROR - Invalid Port Number %d located in instruction %d.\n"
#define IO_ERROR L"ERROR: Cannot find or open the file %s. Please ensure that this file exists, and can be opened.\n"
#define NO_ASM_FILES L"ERROR: Failure to find any asm files in directory to use. Check that they are present and have the .asm suffix.\n"
#define CONST_TOO_LARGE L"ERROR: Constant %d too large for bit size %d.\n"
#define CONST_TOO_SMALL L"ERROR: Constant %d too small for bit size %d.\n"
#define CONST_NEG L"ERROR: Constant %d cannot be negative.\n"

#define CHECKHEAP(s, param) if (debug) { fwprintf(stderr, s, param); BitEpicness::Assembler::CheckHeap(); }

// Input Flags
#define DEBUG_FLAG L"-d"
#define UNIT_TEST_FLAG L"-u"
#define PRINT_FLAG L"-p"
#define AUTO_OUT_FLAG L"-a"
#define HELP_FLAG L"-h"
#define OUT_FLAG L"-o"
#define SD_OUT_FLAG L"-s"
#define BOOTSTRAP_FLAG L"-b"

// Unit Test Settings
#define OVERALL_START L"Starting Unit Test of Assembler in working directory \n%s...\n"
#define OPCODE_START L"Testing GetOpCode...\n"
#define OPCODE_RESULTS L"Input: %s\tOpCode: %s\tFunction Code: %3s\tOpType: %d\tError: %d\n"
#define OPCODE_CONCL L"Done Testing GetOpCode With %d Errors.\n"
#define REG_START L"Testing TranslateRegister...\n"
#define REG_RESULTS L"Input: %-6s\tTranslated Register: %4s\t\t\t\tError: %d\n"
#define REG_CONCL L"Done Testing TranslateRegister With %d Errors.\n"
#define BIN_START L"Testing ConvertDecToBinary...\n"
#define BIN_RESULTS L"Input: %d\t\tOutput: %16s\t\t\tError: %d\n"
#define BIN_CONCL L"Done Testing ConvertDecToBinary With %d Errors.\n"
#define PROCESS_START L"Testing ProcessInstruction...\n"
#define PROCESS_RESULTS L"Input: %-38sError Code: %-15dError: %d\n"
#define PROCESS_CONCL L"Done Testing ProcessInstruction With %d Errors.\n"
#define OVERALL_CONCL L"All Testing Finished with %d Errors.\n"
#define PASS L"PASS"
#define FAIL L"FAIL"
#define fopen _tfopen_s
#endif
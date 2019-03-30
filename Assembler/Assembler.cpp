// Assembler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static bool debug;

namespace BitEpicness
{
	namespace Assembler
	{
		static ErrorHandler* errors;
		errno_t ConvertDecToBinary(int num, int bitSize, TCHAR** binaryNum);

#pragma region OpCodeArrays
		/**************************************************************************************/
		// Variables describing translation of operations. 
		const TCHAR* JTypeOps[J_OPS_LEN] = {L"j", L"jal"};
		const TCHAR* b_JTypeOps[J_OPS_LEN] = {L"00000", L"00001"};
		const TCHAR* RTypeOps[R_OPS_LEN] = {L"beq", L"bgt", L"blt", L"bne", L"lwn", L"swn", L"ldw", L"sdw"};
		const TCHAR* b_RTypeOps[R_OPS_LEN] = {L"1010", L"1000", L"1001", L"1011", L"1110", L"1111", L"1100", L"1101"};
		const TCHAR* ITypeOps[I_OPS_LEN] = {L"addi", L"ori", L"slli"};
		const TCHAR* b_ITypeOps[I_OPS_LEN] = {L"01100", L"01101", L"01111"};
		const TCHAR* MTypeOps[M_OPS_LEN] = {L"add", L"and", L"jr", L"move", L"neg", L"nop", L"not", L"or", L"sll", L"sub"};
		const TCHAR* b_MTypeOps[M_OPS_LEN] = {L"01110", L"01110", L"00010", L"00100", L"00110", L"00100", L"00111", L"01110", L"01110", L"01110"};
		const TCHAR* b_MTypeFuncs[M_OPS_LEN] = {L"000", L"001", L"000", L"000", L"000", L"000", L"000", L"010", L"011", L"110"};
		const TCHAR* LTypeOps[L_OPS_LEN] = {L"ldi", L"ldl"};
		const TCHAR* b_LTypeOps[L_OPS_LEN] = {L"00101", L"01001"};
		const TCHAR* SYSITypeOps[SYSI_OPS_LEN] = {L"wp", L"rp"};
		const TCHAR* b_SYSITypeOps[SYSI_OPS_LEN] = {L"01000", L"01000"};
		const TCHAR* b_SYSITypeFuncs[SYSI_OPS_LEN] = {L"010", L"011"};
		const TCHAR* SYSNTypeOps[SYSN_OPS_LEN] = {L"disi", L"eni"};
		const TCHAR* b_SYSNTypeOps[SYSN_OPS_LEN] = {L"01000", L"01000"};
		const TCHAR* b_SYSNTypeFuncs[SYSN_OPS_LEN] = {L"100", L"101"};
		const TCHAR* SYSRTypeOps[SYSR_OPS_LEN] = {L"swi", L"jalr"};
		const TCHAR* b_SYSRTypeOps[SYSR_OPS_LEN] = {L"01000", L"00011"};
		const TCHAR* b_SYSRTypeFuncs[SYSR_OPS_LEN] = {L"110", L"000"};
		const TCHAR* SYSRRTypeOps[SYSRR_OPS_LEN] = {L"mtc0", L"mfc0"};
		const TCHAR* b_SYSRRTypeOps[SYSRR_OPS_LEN] = {L"01000", L"01000"};
		const TCHAR* b_SYSRRTypeFuncs[SYSRR_OPS_LEN] = {L"000", L"001"};

		// Variables describing translation of registers.
		const TCHAR* Registers[2*REGS_LEN] = {L"$zero", L"$0", L"$at", L"$1", L"$v", L"$2", L"$a", L"$3", L"$s0", L"$4", L"$s1", L"$5", L"$os0", L"$6", L"$os1", L"$7", L"$k0", L"$8", L"$k1", L"$9", L"$k2", L"$10", L"$fp", L"$11", L"$gp", L"$12", L"$sp", 
			L"$13", L"$rr", L"$14", L"$ra", L"$15"};
		const TCHAR* b_Registers[2*REGS_LEN] = {L"0000", L"0000", L"0001", L"0001", L"0010", L"0010", L"0011", L"0011", L"0100", L"0100", L"0101", L"0101", L"0110", L"0110", L"0111", L"0111", L"1000", L"1000", L"1001", L"1001", L"1010", L"1010", L"1011", 
			L"1011", L"1100", L"1100", L"1101", L"1101", L"1110", L"1110", L"1111", L"1111"};

		const TCHAR* C0Registers[C0REGS_LEN] = {L"$epc", L"$cause", L"$br", L"$im", L"$ostmp", L"$mode"};
		const TCHAR* b_C0Registers[C0REGS_LEN] = {L"0000", L"0001", L"0010", L"0011", L"0100", L"0101"};
		/***************************************************************************************/
#pragma endregion

#pragma region Utility Functions
		/*
		*	NAME: ShowCorrectUsage
		*	DESCRIPTION: This function indicates to the user the correct way to use this program, including parameters needed, and optional flags.
		*	USAGE: This should only be used from the main function, while the assembler is understanding what is being asked of it.
		*/
		errno_t ShowCorrectUsage()
		{

			wprintf(L"NAME\n");
			wprintf(L"BitEpicness Assembler\n\n");
			wprintf(L"SYNOPSIS\n");
			wprintf(L"Assembles a BitEpicness assembly file into an executable file for use on a BitEpicness processor. If no output file is indicated, \
					 the binary output will be printed to the command line. Otherwise, the binary output will be written to the given file.\n\n");
			wprintf(L"SYNTAX\n");
			wprintf(L"BitEpicness [-d] [-u] [-p] [-a] <input-file-path> [<output-file-path>]\n\n");
			wprintf(L"FLAGS\n");
			wprintf(L"%-20s%s\n", L"-h", L"Show this help document.");
			wprintf(L"%-20s%s\n", L"-o <OUTPUT_FILE>", L"Output the assembly to the output file indicated.");
			wprintf(L"%-20s%s\n", L"-b", L"Create assembly with bootstrap code, which will automatically call your main function. Use if you are not running this with the OS, or if you are compiling the OS itself.");
			wprintf(L"%-20s%s\n", L"-a", L"The assembled code will be output to a file with the same name as the input, except with a .coe extension. Any indicated output files are ignored.");
			wprintf(L"%-20s%s\n", L"-d", L"Debug information will be printed onto the screen while the assembler runs");
			wprintf(L"%-20s%s\n", L"-p", L"The assembled code will be printed to the screen. This can be used in conjunction with printing to a file.");
			wprintf(L"%-20s%s\n", L"-u", L"The assembler will perform unit tests using the input file provided. There should also be a file with the same name and a .test extension, which has the correct assembly, so that the assembler can check the results.");
			wprintf(L"%-30s%s\n", L"-s", L"Assembles program natively, to allow for quick SD card loading. Name is automatically generated from input name.");
			wprintf(L"EXAMPLES\n");
			wprintf(L"bitepicness -a assembly.asm\n");
			wprintf(L"bitepicness -o instructmem.coe assembly.asm\n");
			return EOK;
		}

		/*
		*	NAME: CheckHeap
		*	DESCRIPTION: This function checks to make sure that the heap is correct, and that there are no loose pointers or other memory problems.
		*	USAGE: This function should only be used inside of a #ifdef DEBUG statement. Otherwise, there will be issues.
		*/
		errno_t CheckHeap() 
		{
			int heapStatus = _heapchk();
			switch(heapStatus) 
			{
			case _HEAPOK:
				wprintf(L"DEBUG: OK - heap is fine\n" );
				return EOK;
			case _HEAPEMPTY:
				wprintf(L"DEBUG: OK - heap is empty\n" );
				return EOK;
			case _HEAPBADBEGIN:
				wprintf(L"DEBUG: ERROR - bad start of heap\n" );
				return EHS;
			case _HEAPBADNODE:
				wprintf(L"DEBUG: ERROR - bad node in heap\n" );
				return EN;
			}
			return EILSEQ;
		}

		errno_t ReplaceExtension(TCHAR* inputFile, TCHAR* extension, TCHAR* outputFile)
		{
			int i;
			int j = 0;
			while(inputFile[j] != '.')
			{
				outputFile[j] = inputFile[j];
				j++;
			}
			for(i = 0; i < (int) wcslen(outputFile); i++)
			{
				outputFile[j++] = extension[i];
			}
			outputFile[j++] = '\0';
			return EOK;
		}

		errno_t GetSize(TCHAR* fileName, int* size)
		{
			FILE* file;
			errno_t errCode = fopen(&file, fileName, L"r");
			*size = 0;
			if (errCode != EOK) 
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, IO_ERROR, fileName);
				return errCode;
			}

			if (fseek(file, 0, SEEK_END) != 0)
			{
				return ESPIPE;
			}
			*size = ftell(file);
			fclose(file);
			return errno;
			
		}

		errno_t ReadCOEFile(TCHAR* coefile, TCHAR** output)
		{
			int size;
			FILE* file;
			GetSize(coefile, &size);
			*output = (TCHAR*) calloc(sizeof(TCHAR), size);
			errno_t errCode = fopen(&file, coefile, L"r");

			if (errCode != EOK) 
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, IO_ERROR, coefile);
				return errCode;
			}

			TCHAR* assembly = (TCHAR*) calloc(sizeof(TCHAR), size);
			while(!feof(file) && (fgetws(assembly, size, file)) != NULL)
			{
				wcscat_s(*output, size, assembly);
			}
			free(assembly);
			fclose(file);
			return errCode;
		}

		TCHAR* TranslateASCII(TCHAR* character)
		{
			TCHAR* bNumChar = (TCHAR*) calloc(sizeof(TCHAR), B_INSTRUCTION_LEN);
			int numChar = character[0];
			if (wcscmp(character, L"\\0") == 0)
			{
				wcscpy_s(bNumChar, B_INSTRUCTION_LEN, L"0000000000000000");
			}
			else
			{
				ConvertDecToBinary(numChar, B_INSTRUCTION_LEN - 1, &bNumChar);
			}
			return bNumChar;
		}
#pragma endregion

#pragma region Assembly I/O

		/*
		*	NAME: GetAssemblySize
		*	DESCRIPTION: This function takes a file name, and returns the number of t_instructions the file contains, and the size in bytes of the file.
		*	USAGE: This function is used by the ReadAssembly function in order to get the dimensions of the file for use in parsing it.
		*/
		errno_t GetAssemblySize(TCHAR* fileName, __out int* numInstructions, __out int* size)
		{

			// Read the file into a HANDLE*.
			FILE* file;
			errno_t errCode = fopen(&file, fileName, L"r");

			if (errCode != EOK) 
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, IO_ERROR, fileName);
				return errCode;
			}

			// Find the total size of the file.
			if (fseek(file, 0, SEEK_END) != 0)
			{
				return ESPIPE;
			}
			*size = ftell(file);
			if (size < 0)
			{
				fclose(file);
				return errno;
			}
			rewind(file);

			/*if (errno > 0)
			{
				fclose(file);
				return errno;
			}*/

			// Get the number of t_instructions present.
			TCHAR* assembly = (TCHAR*) malloc(sizeof(TCHAR)*(*size));
			*numInstructions = 1;

			while((fgetws(assembly, *size, file)) != NULL && !feof(file))
			{
				(*numInstructions)++;
			}
			free(assembly);
			fclose(file);
			return EOK;
		}

		errno_t ReadInstruction(TCHAR* instruction, __out TCHAR* cleaned_instructions)
		{
			int i = 0;
			int j = 0;
			TCHAR c;
			int lastIsSpace = 0;
			int lastIsComment = 0;
			TCHAR* tmpStr = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);

			while((c = instruction[i]) != L'\n' && c != L'\0')
			{
				if (c == L'/' && lastIsComment == 1)
				{
					tmpStr[j - 1] = L'\0';
					wcscpy_s(cleaned_instructions, MAX_INST_STR_LEN, tmpStr);
					free(tmpStr);
					return EOK;
				}
				else if (!isspace(c))
				{
					if (c == L'/')
					{
						lastIsComment = 1;
					}
					tmpStr[j] = c;
					lastIsSpace = 0;
					j++;
				}
				else if (isspace(c) && lastIsSpace == 0)
				{
					tmpStr[j] = L' ';
					lastIsSpace = 1;
					j++;
				}
				i++;
			}
			tmpStr[i] = L'\0';
			wcscpy_s(cleaned_instructions, MAX_INST_STR_LEN, tmpStr);
			free(tmpStr);
			return EOK;
		}

		/*
		*	NAME: ReadAssembly
		*	DESCRIPTION: This function takes a file name, and returns an array of strings which represent each instruction found in the file, as well as the number of t_instructions found.
		*	USAGE: This function is used inside of the main function in order to parse the file into a structure which the ProcessInstruction method can then use.
		*/
		errno_t ReadAssembly(TCHAR* fileName, bool bootstrap, __out int* numInstructions, __out TCHAR*** t_instructions, __out int* numData, __out TCHAR*** t_data)
		{
			int size = 0;
			int numLines = 0;
			GetAssemblySize(fileName, &numLines, &size);

			// Read the file into a HANDLE*.
			FILE* file;
			errno_t errCode = fopen(&file, fileName, L"r");

			if (errCode) 
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, IO_ERROR, fileName);
				return errCode;
			}

			// Load each instruction into a cell in an array.
			// dbmalloc, electricfence
			*t_instructions = (TCHAR**) calloc(sizeof(TCHAR*), numLines);
			*t_data = (TCHAR**) calloc(sizeof(TCHAR*), numLines);
			int i = 0;
			if (bootstrap)
			{
				(*t_instructions)[i] = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
				wcscpy_s((*t_instructions)[i++], MAX_INST_STR_LEN, L"la $s0, mainint");
				(*t_instructions)[i] = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
				wcscpy_s((*t_instructions)[i++], MAX_INST_STR_LEN, L"jalr $s0");
				(*t_instructions)[i] = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
				wcscpy_s((*t_instructions)[i++], MAX_INST_STR_LEN, L"A1000: j A1000");
			}
			TCHAR* tmpStr = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
			TCHAR* cleanedStr = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);

			while(fgetws(tmpStr, MAX_INST_STR_LEN, file) != NULL && wcsstr(tmpStr, L".data") == NULL)
			{
				ReadInstruction(tmpStr, cleanedStr);
				// See if there was any actual information on this line.
				if (wcslen(cleanedStr) > 1)
				{
					// Handle labels being on a separate line than instruction.
					if (cleanedStr[wcslen(cleanedStr) - 1] == ':')
					{
						TCHAR* instStr = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
						do
						{
							if (fgetws(tmpStr, MAX_INST_STR_LEN, file) == NULL)
							{
								break;
							}
							ReadInstruction(tmpStr, instStr);
						} while (wcslen(instStr) < 2);
						wcscat(cleanedStr, instStr);
						free(instStr);
					}
					(*t_instructions)[i] = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
					wcscpy_s(((*t_instructions)[i++]), MAX_INST_STR_LEN, cleanedStr);
				}
			}
			*numInstructions = i;

			i = 0;
			if (wcsstr(tmpStr, L".data") != NULL)
			{
				while(fgetws(tmpStr, MAX_INST_STR_LEN, file) != NULL)
				{
					ReadInstruction(tmpStr, cleanedStr);
					// Handle labels being on a separate line than instruction.
					if (cleanedStr[wcslen(cleanedStr) - 1] == ':')
					{
						TCHAR* instStr = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
						fgetws(tmpStr, MAX_INST_STR_LEN, file);
						ReadInstruction(tmpStr, instStr);
						wcscat(cleanedStr, instStr);
						free(instStr);
					}
					(*t_data)[i] = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
					wcscpy_s(((*t_data)[i++]), MAX_INST_STR_LEN, cleanedStr);
				}
			}
			*numData = i;

			free(tmpStr);
			free(cleanedStr);

			// Close the file.
			fclose(file);
			return EOK;
		}

		/*
		*	NAME: WriteAssembly
		*	DESCRIPTION: This function takes a file name and translated byte code, and writes the byte code to the file indicated in the COE file format. 
		*	USAGE: This function is used inside of the main function in order to write the results of the translation if necessary.
		*/
		errno_t WriteAssembly(TCHAR* fileName, TCHAR* byteCode)
		{
			// Read the file into a HANDLE*.
			FILE* file;
			errno_t errCode = fopen(&file, fileName, L"w");

			if (errCode)
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, IO_ERROR, fileName);
				return errCode;
			}
			
			fputws(byteCode, file);

			// Close the file.
			fclose(file);
			return errCode;
		}
		
		/*
		*	NAME: WriteSDAssembly
		*	DESCRIPTION: This function takes a file name and translated byte code, and writes the byte code to the file indicated in a format that is appropriate for loading onto an SD card. 
		*	USAGE: This function is used inside of the main function in order to write the results of the translation if necessary.
		*/
		errno_t WriteSDAssembly(TCHAR* fileName, TCHAR* byteCode)
		{
			// Read the file into a HANDLE*.
			FILE* file;
			errno_t errCode = fopen(&file, fileName, L"wb");

			if (errCode)
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, IO_ERROR, fileName);
				return errCode;
			}

			int i = 0;
			while(byteCode[i] != '\n')
			{
				i++;
			}
			i++;
			while(byteCode[i] != '\n')
			{
				i++;
			}
			int j = 0;
			char currChar = 0;
			while(byteCode[i] != '\0')
			{
				if(byteCode[i] == '1')
				{
					currChar += pow((double) 2, (double) (7 - j));
					j++;
				}
				else if (byteCode[i] == '0')
				{
					j++;
				}
				if (j == 8)
				{
					fputc(currChar, file);
					currChar = 0;
					j = 0;
				}
				i++;
			}
			fputc((char) 0, file);
			// Close the file.
			fclose(file);
			return errCode;
		}

#pragma endregion

#pragma region Interpretation

		/*
		*	NAME: GetOpCode
		*	DESCRIPTION: This function takes an operation, and translates it into the opCode, funcCode and opType for the operation.
		*	USAGE: This function is used inside of ProcessInstructions in order to determine the t_translated opcode.
		*/
		errno_t GetOpCode(TCHAR* operationName, const int numInstruction, __out TCHAR** opCode, __out TCHAR** funcCode, __out OpType* opType) 
		{
			errno_t errCode;
			for(int j = 0; j < M_OPS_LEN; j++)
			{
				if (wcscmp(MTypeOps[j], operationName) == 0)
				{
					*opType = M;
					errCode = wcscpy_s(*opCode, B_OP_LEN, b_MTypeOps[j]);
					if (errCode > 0)
					{
						return errCode;
					}
					errCode = wcscpy_s(*funcCode, B_FUNC_LEN, b_MTypeFuncs[j]);
					return errCode;
				}
			}
			for(int j = 0; j < SYSI_OPS_LEN; j++)
			{
				if (wcscmp(SYSITypeOps[j], operationName) == 0)
				{
					*opType = SYSI;
					errCode = wcscpy_s(*opCode, B_OP_LEN, b_SYSITypeOps[j]);
					if (errCode > 0)
					{
						return errCode;
					}
					errCode = wcscpy_s(*funcCode, B_FUNC_LEN, b_SYSITypeFuncs[j]);
					return errCode;
				}
			}
			for(int j = 0; j < SYSN_OPS_LEN; j++)
			{
				if (wcscmp(SYSNTypeOps[j], operationName) == 0)
				{
					*opType = SYSN;
					errCode = wcscpy_s(*opCode, B_OP_LEN, b_SYSNTypeOps[j]);
					if (errCode > 0)
					{
						return errCode;
					}
					errCode = wcscpy_s(*funcCode, B_FUNC_LEN, b_SYSNTypeFuncs[j]);
					return errCode;
				}
			}
			for(int j = 0; j < SYSR_OPS_LEN; j++)
			{
				if (wcscmp(SYSRTypeOps[j], operationName) == 0)
				{
					*opType = SYSR;
					errCode = wcscpy_s(*opCode, B_OP_LEN, b_SYSRTypeOps[j]);
					if (errCode > 0)
					{
						return errCode;
					}
					errCode = wcscpy_s(*funcCode, B_FUNC_LEN, b_SYSRTypeFuncs[j]);
					return errCode;
				}
			}
			for(int j = 0; j < SYSRR_OPS_LEN; j++)
			{
				if (wcscmp(SYSRRTypeOps[j], operationName) == 0)
				{
					*opType = SYSRR;
					errCode = wcscpy_s(*opCode, B_OP_LEN, b_SYSRRTypeOps[j]);
					if (errCode > 0)
					{
						return errCode;
					}
					errCode = wcscpy_s(*funcCode, B_FUNC_LEN, b_SYSRRTypeFuncs[j]);
					return errCode;
				}
			}
			for(int j = 0; j < J_OPS_LEN; j++)
			{
				if (wcscmp(JTypeOps[j], operationName) == 0)
				{
					*opType = J;
					errCode = wcscpy_s(*opCode, B_OP_LEN, b_JTypeOps[j]);
					return errCode;
				}
			}
			for(int j = 0; j < R_OPS_LEN; j++)
			{
				if (wcscmp(RTypeOps[j], operationName) == 0)
				{
					*opType = R;
					errCode = wcscpy_s(*opCode, B_OP_LEN, b_RTypeOps[j]);
					return errCode;
				}
			}
			for(int j = 0; j < I_OPS_LEN; j++)
			{
				if (wcscmp(ITypeOps[j], operationName) == 0)
				{
					*opType = I;
					errCode = wcscpy_s(*opCode, B_OP_LEN, b_ITypeOps[j]);
					return errCode;
				}
			}
			for(int j = 0; j < L_OPS_LEN; j++)
			{
				if (wcscmp(LTypeOps[j], operationName) == 0)
				{
					*opType = L;
					errCode = wcscpy_s(*opCode, B_OP_LEN, b_LTypeOps[j]);
					return errCode;
				}
			}
			*opType = (OpType) -1;
			BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
			swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors], MAX_ERROR, INVALID_OP, operationName, numInstruction + 1);
			BitEpicness::Assembler::errors->numErrors++;
			return EOK;
		}

		/*
		*	NAME: TranslateRegister
		*	DESCRIPTION: This function translates register names into byte code for those registers.
		*/
		errno_t TranslateRegister(const TCHAR* t_asmReg, const int numInstruction, __out TCHAR** bReg)
		{
			for(int i = 0; i < 2*REGS_LEN; i++)
			{
				if (wcscmp(t_asmReg, Registers[i]) == 0)
				{
					return wcscpy_s(*bReg, B_REG_LEN, b_Registers[i]);
				}
			}
			for(int i = 0; i < C0REGS_LEN; i++)
			{
				if (wcscmp(t_asmReg, C0Registers[i]) == 0)
				{
					return wcscpy_s(*bReg, B_C0REG_LEN, b_C0Registers[i]);
				}
			}
			BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
			BitEpicness::Assembler::errors->numErrors++;
			return swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, INVALID_REG, t_asmReg, numInstruction + 1);
		}

		/*
		*	NAME: GetAddresses
		*	DESCRIPTION: This function parses assembly code in order to extract an array of addresses, an array of the addresses of each label, and a stripped-down version of the 
		*				 assembly which does not have the labels included.
		*	USAGE: This function is called from ProcessINstruction in order to do the preprocessing of the code before assembly.
		*/
		errno_t GetAddresses(TCHAR** assembly, int* numInstructions, TCHAR** data, int numData, __out int** addresses, __out TCHAR*** labels, __out TCHAR*** strippedAssembly, __out TCHAR*** strippedData)
		{
			int currAddress = 0;
			TCHAR* context = NULL;
			errno_t err = EOK;
			int j = 0;
			for(int i = 0; i < *numInstructions; i++, j++)
			{
				// Get Label
				(*labels)[j] = (TCHAR*) calloc(sizeof(TCHAR), MAX_LABEL_LEN);
				(*strippedAssembly)[j] = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
				TCHAR* tmpAssembly = (TCHAR*) calloc(sizeof(TCHAR), wcslen(assembly[i]) + 1);
				wcscpy_s(tmpAssembly, wcslen(assembly[i]) + 1, assembly[i]);
				TCHAR* possibleLabel = wcstok_s(tmpAssembly, L":", &context);
				TCHAR* possibleInstruction = wcstok_s(NULL, L"\n", &context);

				
				if (possibleInstruction != NULL)
				{
					wcscpy_s((*labels)[j], MAX_LABEL_LEN, possibleLabel);
					if (wcslen(possibleInstruction) > 1)
					{
						wcscpy_s((*strippedAssembly)[j], MAX_INST_STR_LEN, possibleInstruction);
					}
					else
					{
						do
						{
							i++;
						} while(i < *numInstructions && wcslen(assembly[i]) < 2);
						if (i < *numInstructions)
						{
							wcscpy_s((*strippedAssembly)[j], MAX_INST_STR_LEN, assembly[i]);
						}
					}
				}
				else
				{
					wcscpy_s((*labels)[j], MAX_LABEL_LEN, L":NotValidLabel:");
					wcscpy_s((*strippedAssembly)[j], MAX_INST_STR_LEN, possibleLabel);
				}

				//Get Address
				(*addresses)[j] = currAddress;
				if (wcsstr((*strippedAssembly)[j], L"ldi") != NULL || wcsstr((*strippedAssembly)[j], L"ldl") != NULL)
				{
					currAddress++;
				}
				else if (wcsstr((*strippedAssembly)[j], L"la") != NULL)
				{
					currAddress += 6;
					for(int k = 0; k < 4; k++)
					{
						(*strippedAssembly)[++j] = (TCHAR*) (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
						(*labels)[j] = (TCHAR*) calloc(sizeof(TCHAR), MAX_LABEL_LEN);
					}
				}
				currAddress++;
				free(possibleLabel);
			}

			*numInstructions = j;

			for(int i = *numInstructions; i < (numData + *numInstructions); i++)
			{
				// Get Label
				int dataIndex = i - *numInstructions;
				(*labels)[i] = (TCHAR*) calloc(sizeof(TCHAR), MAX_LABEL_LEN);
				(*strippedData)[dataIndex] = (TCHAR*) calloc(sizeof(TCHAR), MAX_INST_STR_LEN);
				TCHAR* tmpAssembly = (TCHAR*) calloc(sizeof(TCHAR), wcslen(data[dataIndex]) + 1);
				wcscpy_s(tmpAssembly, wcslen(data[dataIndex]) + 1, data[dataIndex]);
				TCHAR* possibleLabel = wcstok_s(tmpAssembly, L":", &context);
				TCHAR* possibleInstruction = wcstok_s(NULL, L"\n", &context);

				if (possibleInstruction != NULL)
				{
					wcscpy_s((*labels)[i], MAX_LABEL_LEN, possibleLabel);
					wcscpy_s((*strippedData)[dataIndex], MAX_INST_STR_LEN, possibleInstruction);
				}
				else
				{
					wcscpy_s((*labels)[i], MAX_LABEL_LEN, L":NotValidLabel:");
					wcscpy_s((*strippedData)[dataIndex], MAX_INST_STR_LEN, possibleLabel);
				}

				//Get Address
				(*addresses)[i] = currAddress;
				currAddress += 2;
				free(possibleLabel);
			}
			return err;
		}

		errno_t ConvertDecToBinary(int num, int bitSize, TCHAR** binaryNum)
		{
			if (num < -1*pow((long double) 2, bitSize - 1))
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				return swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, CONST_TOO_SMALL, num, bitSize);
			}
			else if (num >= pow((long double) 2, bitSize - 1))
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				return swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, CONST_TOO_LARGE, num, bitSize);
			}
			bool negative = (num < 0);
			if (negative)
			{
				num = -1 * num;
			}
			for(int i = bitSize - 1; i >= 0; i--)
			{
				if (num - pow(2.0, i) >= 0)
				{
					(*binaryNum)[bitSize - i - 1] = L'1';
					num = num - (int) pow(2.0, i);
				}
				else
				{
					(*binaryNum)[bitSize - i - 1] = L'0';
				}
			}
			(*binaryNum)[bitSize] = '\0';
			if (negative)
			{
				bool added = false;
				for(int i = bitSize - 1; i >= 0; i--)
				{
					if (!added && (*binaryNum)[i] == L'1')
					{
						// No change is necessary because the number needs to be added by one. 
						added = true;
					}
					else if (!added)
					{
						(*binaryNum)[i] = L'0';
					}
					// Otherwise, invert the bits.
					else if ((*binaryNum)[i] == L'1')
					{
						(*binaryNum)[i] = L'0';
					}
					else
					{
						(*binaryNum)[i] = L'1';
					}
				}
			}
			return EOK;
		}

		errno_t ConvertDecToBinaryUnsigned(int num, int bitSize, TCHAR** binaryNum)
		{
			if (num < 0)
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				return swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, CONST_NEG, num);
			}
			else if (num >= pow((long double) 2, bitSize))
			{
				BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
				BitEpicness::Assembler::errors->numErrors++;
				return swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors - 1], MAX_ERROR, CONST_TOO_LARGE, num, bitSize);
			}
			for(int i = bitSize - 1; i >= 0; i--)
			{
				if (num - pow(2.0, i) >= 0)
				{
					(*binaryNum)[bitSize - i - 1] = L'1';
					num = num - (int) pow(2.0, i);
				}
				else
				{
					(*binaryNum)[bitSize - i - 1] = L'0';
				}
			}
			(*binaryNum)[bitSize] = '\0';
			return EOK;
		}
#pragma endregion

#pragma region Processing

		/*
		*	NAME: ProcessPseudoInstructions
		*	DESCRIPTION: This function replaces any pseudo-instructions from the stripped assembly with their
		*		actual counterparts.
		*	USAGE: This function is called from ProcessInstructions, before translating all of the instructions.
		*	NOTE: This assumes that the correct amount of space has been made in the array of instructions during the
		*		process of actually getting the label addresses. If this is not the case, data will be overwritten,
		*		and the risk of memory errors becomes high.
		*/
		errno_t ProcessPseudoInstructions(TCHAR** strippedAssembly, int numInstructions, int numData, int* addresses, TCHAR** labels)
		{
			errno_t err = EOK;
			for(int i = 0; i < numInstructions; i++)
			{
				if (wcsstr(strippedAssembly[i], L"la") != NULL)
				{
					TCHAR* address = (TCHAR*) calloc(sizeof(TCHAR), MAX_LABEL_LEN);
					TCHAR* rd = (TCHAR*) calloc(sizeof(TCHAR), REG_LEN);
					int offset = 0;
					while(isspace((int) strippedAssembly[i][offset]))
					{
						offset++;
					}
					swscanf_s(strippedAssembly[i] + offset, L"la%*[ \t]%[^ ,\t]%*[ ,\t]%[^ ,\n\t]", rd, REG_LEN, address, MAX_LABEL_LEN);
					int iaddress = -1;
					for(int j = 0; j < numInstructions + numData; j++)
					{
						if (wcscmp(labels[j], address) == 0)
						{
							iaddress = addresses[j];
							break;
						}
					}
					if (iaddress == -1)
					{
						BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
						swprintf_s(BitEpicness::Assembler::errors->errorMessages[BitEpicness::Assembler::errors->numErrors], MAX_ERROR, INVALID_LABEL, address, i + 1);
						BitEpicness::Assembler::errors->numErrors++;
						return err;
					}
					else
					{
						swprintf_s(strippedAssembly[i], MAX_INST_STR_LEN, L"ldl $at, %d", iaddress >> 16);
						swprintf_s(strippedAssembly[i + 1], MAX_INST_STR_LEN, L"ldl %s, %d", rd, iaddress & 0x0000FFFF);
						swprintf_s(strippedAssembly[i + 2], MAX_INST_STR_LEN, L"slli $at, 16");
						swprintf_s(strippedAssembly[i + 3], MAX_INST_STR_LEN, L"add $rr, %s", rd);
						swprintf_s(strippedAssembly[i + 4], MAX_INST_STR_LEN, L"move %s, $rr", rd);
					}
				}
			}
			return err;
		}

		/*
		*	NAME: ProcessInstruction
		*	DESCRIPTION: This function translates assembly, which contains numInstructions, into bytecode and returns it through byteCode.
		*	USAGE: This function should only be called from inside of main.
		*/
		errno_t ProcessInstructions(TCHAR** assembly, int numInstructions, TCHAR** data, int numData, __out TCHAR** byteCode)
		{
			int currAddress = 0;
			int* addresses = (int*) calloc(sizeof(int), MAX_INSTS_PER_INSTRUCTION*numInstructions);
			TCHAR** labels = (TCHAR**) calloc(sizeof(TCHAR*), MAX_INSTS_PER_INSTRUCTION*numInstructions);
			TCHAR** strippedAssembly = (TCHAR**) calloc(sizeof(TCHAR*), MAX_INSTS_PER_INSTRUCTION*numInstructions);
			TCHAR** strippedData = (TCHAR**) calloc(sizeof(TCHAR*), numData);

			errno_t errCode = GetAddresses(assembly, &numInstructions, data, numData, &addresses, &labels, &strippedAssembly, &strippedData);

			*byteCode = (TCHAR*) calloc(sizeof(TCHAR), B_CODE_SIZE);
			
			errCode |= ProcessPseudoInstructions(strippedAssembly, numInstructions, numData, addresses, labels);

			swprintf_s(*byteCode, B_HEADER_LENGTH, L"memory_initialization_radix=2;\nmemory_initialization_vector=\n");

			for(int i = 0; i < numInstructions && wcscmp(strippedAssembly[i], L".data") != 0; i++) 
			{
				if (i != 0)
				{
					wcscat_s(*byteCode, B_CODE_SIZE, L",\n");
				}
				TCHAR* op = (TCHAR*) calloc(OP_LEN, sizeof(TCHAR));
				TCHAR* opCode = (TCHAR*) calloc(B_OP_LEN, sizeof(TCHAR));
				TCHAR* func = (TCHAR*) calloc(B_FUNC_LEN, sizeof(TCHAR));
				TCHAR* parameters = (TCHAR*) calloc(MAX_INST_STR_LEN, sizeof(TCHAR));
				OpType opType;
				errno = 0;
				swscanf_s(strippedAssembly[i], L"%s %[^\n]", op, OP_LEN, parameters, MAX_INST_STR_LEN);
				errCode |= errno;
				errCode |= GetOpCode(op, i, &opCode, &func, &opType);
				int imm = -1;
				int numAssigned = -1;
				TCHAR* rs = (TCHAR*) calloc(REG_LEN, sizeof(TCHAR));
				TCHAR* rt = (TCHAR*) calloc(REG_LEN, sizeof(TCHAR));
				TCHAR* rd = (TCHAR*) calloc(REG_LEN, sizeof(TCHAR));
				TCHAR* translatedRs = (TCHAR*) calloc(B_REG_LEN, sizeof(TCHAR));
				TCHAR* translatedRt = (TCHAR*) calloc(B_REG_LEN, sizeof(TCHAR));
				TCHAR* translatedRd = (TCHAR*) calloc(B_REG_LEN, sizeof(TCHAR));
				TCHAR* translatedImm = (TCHAR*) calloc(B_IMM_LEN, sizeof(TCHAR));
				TCHAR* translatedLImm = (TCHAR*) calloc(B_INSTRUCTION_LEN, sizeof(TCHAR));
				TCHAR* target = (TCHAR*) calloc(MAX_LABEL_LEN, sizeof(TCHAR));
				TCHAR* translatedTarget = (TCHAR*) calloc(B_TARGET_LEN + 1, sizeof(TCHAR));
				TCHAR* translatedInstruction = (TCHAR*) calloc((B_INSTRUCTION_LEN + 1)*B_MAX_WORDS_PER_INSTRUCTION, sizeof(TCHAR));
				switch(opType)
				{
				case R:
					swscanf_s(parameters, L"%[^ ,]%*[, ]%[^ ,]%*[, ]%[^ ,]", rd, REG_LEN, rs, REG_LEN, rt, REG_LEN);
					errCode |= errno;
					errCode |= TranslateRegister(rs, i, &translatedRs);
					errCode |= TranslateRegister(rt, i, &translatedRt);
					errCode |= TranslateRegister(rd, i, &translatedRd);
					swprintf_s(translatedInstruction, B_INSTRUCTION_LEN + 2, L"%s%s%s%s%s", opCode, translatedRd, translatedRs, translatedRt, func);
					break;
				case I:
					swscanf_s(parameters, L"%[^ ,]%*[ ,]%d", rd, REG_LEN, &imm);
					errCode |= TranslateRegister(rd, i, &translatedRd);
					errCode |= ConvertDecToBinary(imm, 7, &translatedImm);
					swprintf_s(translatedInstruction, B_INSTRUCTION_LEN + 2, L"%s%s%s", opCode, translatedRd, translatedImm);
					break;
				case J:
					swscanf_s(parameters, L"%s", target, MAX_LABEL_LEN);
					for(int j = 0; j < numInstructions; j++)
					{
						if (wcscmp(labels[j], target) == 0)
						{
							imm = addresses[j];
							break;
						}
					}
					errCode |= ConvertDecToBinary(imm, B_TARGET_LEN, &translatedTarget);
					// TODO: Check the addressing structure for jumps and branches.
					swprintf_s(translatedInstruction, B_INSTRUCTION_LEN + 2, L"%s%s", opCode, translatedTarget);
					break;
				case M:
					swscanf_s(parameters, L"%[^ ,]%*[ ,]%[^ ,]", rd, REG_LEN, rs, REG_LEN);
					if (wcscmp(rs, L"") == 0)
					{
						errCode |= wcscpy_s(rs, REG_LEN, L"$0");
					}
					if (wcscmp(rd, L"") == 0)
					{
						errCode |= wcscpy_s(rd, REG_LEN, L"$0");
					}
					errCode |= TranslateRegister(rs, i, &translatedRs);
					errCode |= TranslateRegister(rd, i, &translatedRd);
					swprintf_s(translatedInstruction, B_INSTRUCTION_LEN + 2, L"%s%s%s%s", opCode, translatedRd, translatedRs, func);
					break;
				case L:
					numAssigned = swscanf_s(parameters, L"%[^ ,]%*[ ,]%d", rd, REG_LEN, &imm);
					if (numAssigned == 1)
					{
						swscanf_s(parameters, L"%[^ ,]%*[ ,]%s", rd, REG_LEN, target, MAX_LABEL_LEN);
						imm = -1;
						for(int j = 0; j < numInstructions; j++)
						{
							if (wcscmp(target, labels[j]) == 0)
							{
								imm = addresses[j];
								break;
							}
						}
					}
					errCode |= ConvertDecToBinary(imm, B_INSTRUCTION_LEN - 1, &translatedLImm);
					errCode |= TranslateRegister(rd, i, &translatedRd);
					swprintf(translatedInstruction, 2*B_INSTRUCTION_LEN + 5, L"%s%s0000000,\n%s", opCode, translatedRd, translatedLImm);
					break;
				case SYSI:
					swscanf_s(parameters, L"%[^ ,]%*[ ,]%d", rd, REG_LEN, &imm);
					if (imm < 0)
					{
						errors->errorMessages[errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
						swprintf_s(errors->errorMessages[errors->numErrors], MAX_ERROR, INVALID_PORT_NO, imm, i);
						errors->numErrors++;
						errCode = OPERR;
						break;
					}
					errCode |= TranslateRegister(rd, i, &translatedRd);

					//This strange code allows unsigned port numbers to be allowed through.
					errCode |= ConvertDecToBinaryUnsigned(imm, B_C0REG_LEN, &translatedTarget);
					swprintf_s(translatedInstruction, B_INSTRUCTION_LEN + 2, L"%s%s%s%s", opCode, translatedRd, translatedTarget + 1, func);
					break;
				case SYSN:
					swprintf_s(translatedInstruction, B_INSTRUCTION_LEN + 2, L"%s00000000%s", opCode, func);	
					break;
				case SYSR:
					swscanf_s(parameters, L"%[^ ,]", rd, REG_LEN);
					errCode |= TranslateRegister(rd, i, &translatedRd);
					swprintf_s(translatedInstruction, B_INSTRUCTION_LEN + 2, L"%s%s0000%s", opCode, translatedRd, func);
					break;
				case SYSRR:
					swscanf_s(parameters, L"%[^ ,]%*[ ,]%s", rd, REG_LEN, rt, REG_LEN);
					errCode |= TranslateRegister(rd, i, &translatedRd);
					errCode |= TranslateRegister(rt, i, &translatedRt);
					swprintf(translatedInstruction, B_INSTRUCTION_LEN + 2, L"%s%s%s%s", opCode, translatedRd, translatedRt, func);
					break;
				default:
					errors->errorMessages[errors->numErrors] = (TCHAR*) calloc(MAX_ERROR, sizeof(TCHAR));
					swprintf_s(errors->errorMessages[errors->numErrors], MAX_ERROR, INVALID_OP_TYPE, i);
					errors->numErrors++;
					errCode = OPERR;
					break;
				}
				wcscat_s(*byteCode, B_CODE_SIZE, translatedInstruction);
				free(rs);
				free(rt);
				free(rd);
				free(translatedRs);
				free(translatedRt);
				free(translatedRd);
				free(translatedImm);
				free(translatedLImm);
				free(target);
				free(translatedTarget);
				free(op);
				free(opCode);
				free(func);
				free(parameters);
				free(translatedInstruction);
			}

			for(int i = 0; i < numData; i++)
			{
				wcscat_s(*byteCode, B_CODE_SIZE, L",\n0000000000000000,\n");
				TCHAR* c = TranslateASCII(strippedData[i]);
				wcscat_s(*byteCode, B_CODE_SIZE, c);
			}

			wcscat_s(*byteCode, B_CODE_SIZE, L";");

			free(addresses);
			for(int i = 0; i < numInstructions; i++)
			{
				free(labels[i]);
				free(strippedAssembly[i]);
			}
			free(strippedAssembly);
			free(labels);
			return errCode;
		}

		errno_t AssembleInstructions(TCHAR* inputFile, bool bootstrap, TCHAR** output)
		{
			TCHAR** t_instructions;
			errno_t errorCode;
			int numInstructions = -1;
			TCHAR** t_data;
			int numData = -1;
			
			CHECKHEAP(L"DEBUG: Reading file %s.\n", inputFile);
			errorCode = ReadAssembly(inputFile, bootstrap, &numInstructions, &t_instructions, &numData, &t_data);
			CHECKHEAP(L"DEBUG: Code has been read from the file successfully with error code %d.\n", errorCode);
			
			if (errorCode == EOK)
			{
				*output = (TCHAR*) calloc(B_CODE_SIZE, sizeof(TCHAR));
				errorCode = ProcessInstructions(t_instructions, numInstructions, t_data, numData, output);
				for(int i = 0; i < numInstructions; i++)
				{
					free(t_instructions[i]);
				}
				free(t_instructions);
			}
			if (errorCode != EOK)
			{
				for(int i = 0; i < errors->numErrors; i++)
				{
					wprintf(errors->errorMessages[i]);
					free(errors->errorMessages[i]);
				}
			}
			return errorCode;
		}
#pragma endregion
	}
}

#pragma region Unit Tests
extern "C" __declspec(dllexport) int Test_GetOpCode(TCHAR* operationName, TCHAR* opCode, TCHAR* funcCode)
{
	BitEpicness::Assembler::errors = (BitEpicness::Assembler::ErrorHandler*) malloc(sizeof(BitEpicness::Assembler::ErrorHandler));
	BitEpicness::Assembler::errors->numErrors = 0;
	BitEpicness::Assembler::errors->errorMessages = (TCHAR**) calloc(MAX_NUM_ERRORS, sizeof(TCHAR*));

	TCHAR* wOpCode = (TCHAR*) calloc(B_OP_LEN, sizeof(TCHAR));
	TCHAR* wFuncCode = (TCHAR*) calloc(B_FUNC_LEN, sizeof(TCHAR));
	BitEpicness::Assembler::OpType wOpType;
	BitEpicness::Assembler::GetOpCode(operationName, 1, &wOpCode, &wFuncCode, &wOpType);

	wcscpy(opCode, wOpCode);
	wcscpy(funcCode, wFuncCode);
	return wOpType;
}

extern "C" __declspec(dllexport) void Test_TranslateRegister(TCHAR* inReg, TCHAR* outReg)
{
	BitEpicness::Assembler::errors = (BitEpicness::Assembler::ErrorHandler*) malloc(sizeof(BitEpicness::Assembler::ErrorHandler));
	BitEpicness::Assembler::errors->numErrors = 0;
	BitEpicness::Assembler::errors->errorMessages = (TCHAR**) calloc(MAX_NUM_ERRORS, sizeof(TCHAR*));

	TCHAR* wOutReg = (TCHAR*) calloc(B_C0REG_LEN, sizeof(TCHAR));
	BitEpicness::Assembler::TranslateRegister(inReg, 1, &wOutReg);

	wcscpy(outReg, wOutReg);
}

extern "C" __declspec(dllexport) void Test_ConvertDecToBinary(int decimal, int bitnum, int* numErrors, TCHAR* binary)
{
	BitEpicness::Assembler::errors = (BitEpicness::Assembler::ErrorHandler*) malloc(sizeof(BitEpicness::Assembler::ErrorHandler));
	BitEpicness::Assembler::errors->numErrors = 0;
	BitEpicness::Assembler::errors->errorMessages = (TCHAR**) calloc(MAX_NUM_ERRORS, sizeof(TCHAR*));

	TCHAR* wBinary = (TCHAR*) calloc(bitnum + 1, sizeof(TCHAR));
	BitEpicness::Assembler::ConvertDecToBinary(decimal, bitnum, &wBinary);
	
	if (BitEpicness::Assembler::errors->numErrors > 0)
	{
		wcscpy(binary, L"ERROR");
		*numErrors = BitEpicness::Assembler::errors->numErrors;
	}
	else
	{
		wcscpy(binary, wBinary);
	}
}

extern "C" __declspec(dllexport) void Test_TranslateSingleInstruction(TCHAR* assemblyLine, int strLen, int numInstructions, TCHAR* binaryAsm)
{
	TCHAR* wBinary = (TCHAR*) calloc(strLen, sizeof(TCHAR));
	TCHAR** wAsmArr = (TCHAR**) calloc(numInstructions, sizeof(TCHAR*));
	TCHAR* assemblyCopy = (TCHAR*) calloc(wcslen(assemblyLine) + 1, sizeof(TCHAR));
	wcscpy_s(assemblyCopy, wcslen(assemblyLine) + 1, assemblyLine);
	TCHAR* line = wcstok(assemblyCopy, L"\n");
	for(int i = 0; i < numInstructions; i++)
	{
		wAsmArr[i] = (TCHAR*) calloc(wcslen(line) + 1, sizeof(TCHAR));
		wcscpy_s(wAsmArr[i], wcslen(line) + 1, line);
		line = wcstok(NULL, L"\n");
	}
	TCHAR** dataArr = (TCHAR**) calloc(1, sizeof(TCHAR*));
	dataArr[0] = (TCHAR*) calloc(B_INSTRUCTION_LEN, sizeof(TCHAR));
	BitEpicness::Assembler::ProcessInstructions(wAsmArr, numInstructions, dataArr, 0, &wBinary);
	wcscpy_s(binaryAsm, strLen, wBinary);
}

extern "C" __declspec(dllexport) void Test_TranslateInstruction(TCHAR* fileName, int fileLength, TCHAR* translatedAsm)
{
	BitEpicness::Assembler::errors = (BitEpicness::Assembler::ErrorHandler*) malloc(sizeof(BitEpicness::Assembler::ErrorHandler));
	BitEpicness::Assembler::errors->numErrors = 0;
	BitEpicness::Assembler::errors->errorMessages = (TCHAR**) calloc(MAX_NUM_ERRORS, sizeof(TCHAR*));

	TCHAR* byteCode = (TCHAR*) calloc(sizeof(TCHAR), fileLength + 1);
	BitEpicness::Assembler::AssembleInstructions(fileName, true, &byteCode);

	wcscpy(translatedAsm, byteCode);
}

#pragma endregion

#pragma region Main

/*
*	NAME: ParseInputFlags
*	DESCRIPTION: This function parses the flags indicated by argv and argc, and sets the other arguments correctly depending on the flags that are set.
*	USAGE: This function should be called in main, where the output parameters of this function are used in order to determine the appropriate course of action.
*/
void ParseInputFlags(TCHAR** argv, int argc, bool* debug, bool* print, bool* autoout, bool* help, bool* outfile, TCHAR* outputFile, bool* sdcardout, TCHAR* asmPath, bool* bootstrap)
{
	for(int i = 1; i < argc; i++)
	{
		if (wcscmp(argv[i], DEBUG_FLAG) == 0)
		{
			*debug = true;
		}
		else if (wcscmp(argv[i], PRINT_FLAG) == 0)
		{
			*print = true;
		}
		else if (wcscmp(argv[i], AUTO_OUT_FLAG) == 0)
		{
			*autoout = true;
		}
		else if (wcscmp(argv[i], HELP_FLAG) == 0)
		{
			*help = true;
		}
		else if (wcscmp(argv[i], OUT_FLAG) == 0)
		{
			if (i + 2 < argc)
			{
				wcsncpy_s(outputFile, FILENAME_MAX, argv[i + 1], _TRUNCATE);
				*outfile = true;
				i++;
			}
			else
			{
				*print = true;
				break;
			}
		}
		else if (wcscmp(argv[i], SD_OUT_FLAG) == 0)
		{
			*sdcardout = true;
		}
		else if (wcscmp(argv[i], BOOTSTRAP_FLAG) == 0)
		{
			*bootstrap = true;
		}
		else
		{
			wcsncpy_s(asmPath, FILENAME_MAX, argv[i], _TRUNCATE);
			if (i + 1 < argc)
			{
				wcsncpy_s(outputFile, FILENAME_MAX, argv[i + 1], _TRUNCATE);
				*outfile = true;
			}
			else if (*autoout)
			{
				BitEpicness::Assembler::ReplaceExtension(argv[i], L".coe", outputFile);
				*outfile = true;
			}
			break;
		}
	}
}

/*
*	NAME: _tmain
*	DESCRIPTION: This function is the starting point of the assembler, and uses the results of parsing the flags in order to do correct procedure.
*	USAGE: This function should not be called by developer code, and should not contain any domain code, only controller code for other functions.
*/
int _tmain(int argc, TCHAR* argv[])
{
	errno_t errorCode;
	BitEpicness::Assembler::errors = (BitEpicness::Assembler::ErrorHandler*) malloc(sizeof(BitEpicness::Assembler::ErrorHandler));
	BitEpicness::Assembler::errors->numErrors = 0;
	BitEpicness::Assembler::errors->errorMessages = (TCHAR**) calloc(MAX_NUM_ERRORS, sizeof(TCHAR*));
	TCHAR* asmPath = (TCHAR*) calloc(FILENAME_MAX, sizeof(TCHAR));
	TCHAR* outputFile = (TCHAR*) calloc(sizeof(TCHAR), FILENAME_MAX);
	TCHAR* binOutputFile = (TCHAR*) calloc(sizeof(TCHAR), FILENAME_MAX);
	int i;

	TCHAR* output = (TCHAR*) calloc(sizeof(TCHAR), 100);
	Test_TranslateSingleInstruction(L"wp $s0, 8", 100, 1, output);
	free(output);
	bool print = false;
	bool autoout = false;
	bool outfile = false;
	bool help = false;
	bool bootstrap = false;
	bool sdcardout = false;
	ParseInputFlags(argv, argc, &debug, &print, &autoout, &help, &outfile, outputFile, &sdcardout, asmPath, &bootstrap);

	if (argc <= 1 || help) 
	{
		// This is not the correct usage of the program.
		BitEpicness::Assembler::ShowCorrectUsage();
		return 0;
	}
	CHECKHEAP(L"", NULL);
	TCHAR* byteCode;
	errorCode = BitEpicness::Assembler::AssembleInstructions(asmPath, bootstrap, &byteCode);
	CHECKHEAP(L"", NULL);
	if (errorCode == EOK)
	{
		if (print)
		{	
			wprintf(L"%s\n", byteCode);
		}
		if (sdcardout)
		{
			if (outfile)
			{
				BitEpicness::Assembler::WriteSDAssembly(outputFile, byteCode);
			}
			else
			{
				BitEpicness::Assembler::ReplaceExtension(argv[argc - 1], L".bin", binOutputFile);
				BitEpicness::Assembler::WriteSDAssembly(binOutputFile, byteCode);
			}
		}
		else if (outfile)
		{
			BitEpicness::Assembler::WriteAssembly(outputFile, byteCode);
		}
		CHECKHEAP(L"DEBUG: Converted to \n%s\n", byteCode);
		free(byteCode);
		free(outputFile);
	}
	free(BitEpicness::Assembler::errors->errorMessages);
	free(BitEpicness::Assembler::errors);
	_CrtDumpMemoryLeaks();
	return 0;
}
#pragma endregion

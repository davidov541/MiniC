// Assembler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

namespace BitEpicness
{
	namespace Assembler
	{
		/*
		*	NAME: ShowCorrectUsage
		*	DESCRIPTION: This function indicates to the user the correct way to use this program, including parameters needed, and optional flags.
		*	USAGE: This should only be used from the main function, while the assembler is understanding what is being asked of it.
		*/
		errno_t ShowCorrectUsage();

		/*
		*	NAME: CheckHeap
		*	DESCRIPTION: This function checks to make sure that the heap is correct, and that there are no loose pointers or other memory problems.
		*	USAGE: This function should only be used inside of a #ifdef DEBUG statement. Otherwise, there will be issues.
		*/
		errno_t CheckHeap();

		errno_t ReplaceExtension(TCHAR* inputFile, TCHAR* extension, TCHAR* outputFile);

		errno_t GetSize(TCHAR* fileName, int* size);

		errno_t ReadCOEFile(TCHAR* coefile, TCHAR** output);

		/*
		*	NAME: GetAssemblySize
		*	DESCRIPTION: This function takes a file name, and returns the number of t_instructions the file contains, and the size in bytes of the file.
		*	USAGE: This function is used by the ReadAssembly function in order to get the dimensions of the file for use in parsing it.
		*/
		errno_t GetAssemblySize(TCHAR* fileName, __out int* numInstructions, __out int* size);

		errno_t ReadInstruction(TCHAR* instruction, __out TCHAR** cleaned_instructions);

		/*
		*	NAME: ReadAssembly
		*	DESCRIPTION: This function takes a file name, and returns an array of strings which represent each instruction found in the file, as well as the number of t_instructions found.
		*	USAGE: This function is used inside of the main function in order to parse the file into a structure which the ProcessInstruction method can then use.
		*/
		errno_t ReadAssembly(TCHAR* fileName, bool bootstrap, __out int* numInstructions, __out TCHAR*** t_instructions);

		/*
		*	NAME: WriteAssembly
		*	DESCRIPTION: This function takes a file name and translated byte code, and writes the byte code to the file indicated. 
		*	USAGE: This function is used inside of the main function in order to write the results of the translation if necessary.
		*/
		errno_t WriteAssembly(TCHAR* fileName, TCHAR* byteCode);

		errno_t WriteSDAssembly(TCHAR* fileName, TCHAR* byteCode);

		/*
		*	NAME: GetOpCode
		*	DESCRIPTION: This function takes an operation, and translates it into the opCode, funcCode and opType for the operation.
		*	USAGE: This function is used inside of ProcessInstructions in order to determine the t_translated opcode.
		*/
		errno_t GetOpCode(TCHAR* operationName, const int numInstruction, __out TCHAR** opCode, __out TCHAR** funcCode, __out OpType* opType);

		/*
		*	NAME: TranslateRegister
		*	DESCRIPTION: This function translates register names into byte code for those registers.
		*/
		errno_t TranslateRegister(const TCHAR* t_asmReg, const int numInstruction, __out TCHAR** bReg);
		
		/*
		*	NAME: GetAddresses
		*	DESCRIPTION: This function parses assembly code in order to extract an array of addresses, an array of the addresses of each label, and a stripped-down version of the 
		*				 assembly which does not have the labels included.
		*	USAGE: This function is called from ProcessINstruction in order to do the preprocessing of the code before assembly.
		*/
		errno_t GetAddresses(TCHAR** assembly, int numInstructions, __out int** addresses, __out TCHAR*** labels, __out TCHAR*** strippedAssembly);

		errno_t ConvertDecToBinary(int num, int bitSize, TCHAR** binaryNum);

		errno_t ConvertDecToBinaryUnsigned(int num, int bitSize, TCHAR** binaryNum);

		/*
		*	NAME: ProcessInstruction
		*	DESCRIPTION: This function translates assembly, which contains numInstructions, into bytecode and returns it through byteCode.
		*	USAGE: This function should only be called from inside of main.
		*/
		errno_t ProcessInstructions(TCHAR** assembly, int numInstructions, __out TCHAR** byteCode);

		errno_t AssembleInstructions(TCHAR* inputFile, bool bootstrap, TCHAR** output);
	}
}
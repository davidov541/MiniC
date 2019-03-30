#pragma once
#include "Scanner.h"
#include "Parser.h"
#include "Node.h"
#include "ErrorHandler.h"
#include "SymbolTable.h"
#include "FlowGraph.h"
//#include "BasicBlock.h"
//#include "CodeGen.h"
//#include "Instruction.h"

#define CHECKHEAP if(debug > 0) CheckHeap();

void PrintHelp();
int ParseFlags(TCHAR** argv, int argc, bool* help, bool* version, bool* writeToOutput, bool* assemble, bool* print, bool* assembleOnly, bool* bootload, bool* taskFound, bool* sdCardOut, int* debug, std::wstring* asmOut, std::wstring* coeOut);
void RunUnitTests();
bool Compile(std::wstring srcFile, bool bootload, int debug, std::wstring* output);

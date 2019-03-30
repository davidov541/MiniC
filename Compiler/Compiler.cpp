// Compiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Compiler.h"


#pragma region Utility Functions
void PrintHelp()
{
	wprintf(L"MINIC Version %s\n", VERSION_NO);
	wprintf(L"usage: minic [OPTIONS] FILE\n");
	wprintf(L"%-30s%s\n", L"-h", L"Display this information.");
	wprintf(L"%-30s%s\n", L"--help", L"Display this information.");
	wprintf(L"%-30s%s\n", L"-v", L"Display minic version.");
	wprintf(L"%-30s%s\n", L"-o [<file>]", L"Compile and assemble. The optional file argument indicates where to put the assembled code. No argument indicates it should be printed to the screen."); 
	wprintf(L"%-30s%s\n", L"-c [<file>]", L"Compile but do not assemble. The optional file argument indicates where to put the assembled code. No argument indicates it should be printed to the screen."); 
	wprintf(L"%-30s%s\n", L"-d <code>", L"Output debug information while running according to the code, as explained below. All stage declarations will be displayed as long as the code is greater than 0."); 
	wprintf(L"%-30s%s\n", L"-a [<file>]", L"Only assemble the file for Epicness architecture. The optional file argument indicates where to put the assembled code. No argument indicates it should be printed to the screen.");
	wprintf(L"%-30s%s\n", L"-b", L"Compile code in OS mode, which will expect interrupt handler to be defined, and use bootloader code in order to call main.");	
	wprintf(L"%-30s%s\n", L"-u", L"Run unit tests on the compiler.");
	wprintf(L"%-30s%s\n", L"-s", L"Assembles program natively, to allow for quick SD card loading. Name is automatically generated from output name. Implies assembling will be done.");
	wprintf(L"\n\nDEBUG CODES:\n");
	wprintf(L"%-30s%s\n", L"0", L"No MiniC::ErrorHandler::GetInstance()or messages will be printed.");
	wprintf(L"%-30s%s\n", L"1", L"Error messages will be printed for the syntax expand phase.");
	wprintf(L"%-30s%s\n", L"2", L"Error messages will be printed for the type checking phases.");
	wprintf(L"%-30s%s\n", L"3", L"Error messages will be printed for the conversion to a flow graph.");
	wprintf(L"%-30s%s\n", L"4", L"Error messages will be printed for the code generation phase.");
	wprintf(L"%-30s%s\n", L"5", L"Error messages will be printed for the To_String called before syntax expand.");
	wprintf(L"%-30s%s\n", L"6", L"Error messages will be printed for the To_String called after syntax expand.");
	wprintf(L"%-30s%s\n", L"7", L"Error messages will be printed for the parsing phase.");
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

int ParseFlags(TCHAR** argv, int argc, bool* help, bool* version, bool* writeToOutput, bool* assemble, bool* print, bool* assembleOnly, bool* bootload, bool* taskFound, bool* sdCardOut, int* debug, std::wstring* asmOut, std::wstring* coeOut)
{
	int i = 1;
	for(; i < argc; i++) 
	{
		if (wcscmp(HELP, argv[i]) == 0 || wcscmp(HELPLONG, argv[i]) == 0) 
		{
			*help = true;
			*print = true;
			*taskFound = true;
			break;
		} 
		else if (wcscmp(VERSION, argv[i]) == 0) 
		{
			*version = true;
			*print = true;
			*taskFound = true;
			break;
		} 
		else if (wcscmp(COEOUTPUT, argv[i]) == 0) 
		{
			if (argv[i + 1][0] == '-' || i + 2 >= argc)
			{
				*print = true;
				*writeToOutput = false;
				*asmOut = std::wstring(ASM_TMP_FILE);
			}
			else
			{
				*print = false;
				*writeToOutput = true;
				*coeOut = std::wstring(argv[i + 1]);
				TCHAR* fileName = (TCHAR*) calloc(sizeof(TCHAR), coeOut->size());
				wcscpy_s(fileName, coeOut->size() + 1, coeOut->c_str());
				*asmOut = std::wstring(fileName);
				asmOut->erase(asmOut->rfind(L"."));
				asmOut->append(L".asm");
				i++;
			}
			*assemble = true;
			*assembleOnly = false;
			*taskFound = true;
		} 
		else if (wcscmp(SDCARDOUT, argv[i]) == 0)
		{
			*sdCardOut = true;
		}
		else if (wcscmp(NOASSEMBLE, argv[i]) == 0)
		{
			if (argv[i + 1][0] == '-' || i + 2 >= argc)
			{
				*print = true;
				*writeToOutput = false;
			}
			else
			{
				*print = false;
				*writeToOutput = true;
				*coeOut = std::wstring(L"");
				*asmOut = std::wstring(argv[i + 1]);
				i++;
			}
			*assemble = false;
			*assembleOnly = false;
			*taskFound = true;
		}
		else if (wcscmp(DEBUG, argv[i]) == 0)
		{
			if (argc == i + 1)
			{
				wprintf(NO_DEBUG_CODE);
				return -1;
			}
			*debug = wtoi(argv[i + 1]);
			i++;
		}
		else if (wcscmp(ASSEMBLEONLY, argv[i]) == 0)
		{
			if (argv[i + 1][0] == '-' || i + 2 >= argc)
			{
				*print = true;
				*writeToOutput = false;
			}
			else
			{
				*print = false;
				*writeToOutput = true;
				*coeOut = std::wstring(argv[i + 1]);
				*asmOut = std::wstring(L"");
				i++;
			}
			*assemble = true;
			*assembleOnly = true;
			*taskFound = true;
		}
		else if (wcscmp(BOOTLOADER, argv[i]) == 0)
		{
			*bootload = true;
		}
	}
	return 0;
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

TCHAR* ReplaceStr(TCHAR* str, const TCHAR* orig, const TCHAR* rep)
{
  TCHAR* buffer = (TCHAR*) calloc(sizeof(TCHAR), LINE_LENGTH_MAX);
  TCHAR* p;

  if(!(p = wcsstr(str, orig)))  // Is 'orig' even in 'str'?
  {
    return str;
  }

  char nextChar = (wcslen(orig) + p)[0];

  if ((p[0] != str[0] && isalnum((p - 1)[0])) || isalnum(nextChar))
  {
	  return str;
  }

  wcsncpy_s(buffer, LINE_LENGTH_MAX, str, p - str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  swprintf_s(buffer+(p-str), LINE_LENGTH_MAX - (p - str), L"%s%s", rep, p + wcslen(orig));

  return buffer;
}

TCHAR* ReplaceMacro(TCHAR* str, const TCHAR* macroname, const TCHAR* macrocode, const TCHAR* params)
{
  TCHAR* buffer = (TCHAR*) calloc(sizeof(TCHAR), LINE_LENGTH_MAX);
  TCHAR* p;
  TCHAR* codebuffer = (TCHAR*) calloc(sizeof(TCHAR), wcslen(macrocode) + 1);
  TCHAR* origparams = (TCHAR*) calloc(sizeof(TCHAR), wcslen(macrocode) + 1);
  TCHAR* paramsbuffer = (TCHAR*) calloc(sizeof(TCHAR), wcslen(params) + 1);

  if(!(p = wcsstr(str, macroname))) // Is 'orig' even in 'str'?
  {
		return str;
  }

  char startOfParams = (p + wcslen(macroname))[0];

  if (isalnum((p - 1)[0]) || startOfParams != '(')
  {
	  return str;
  }
  
  wcscpy_s(codebuffer, wcslen(macrocode) + 1, macrocode);
  wcscpy_s(paramsbuffer, wcslen(params) + 1, params);
  TCHAR* param = wcstok(paramsbuffer, L",");
  std::list<std::wstring> paramslist = std::list<std::wstring>();
  int i = 0;
  while(param != NULL)
  {
	  paramslist.push_back(std::wstring(param));
	  param = wcstok(NULL, L",");
  }
  swscanf_s(p, L"%*[^ \n(](%[^\n)]) %*[^\n]", origparams, wcslen(macrocode) + 1);
  TCHAR* origparam = wcstok(origparams, L",");
  i = 0;
  while(origparam != NULL)
  {
	  TCHAR* oldcode;
	  do
	  {
		  oldcode = codebuffer;
		  codebuffer = ReplaceStr(codebuffer, paramslist.front().c_str(), origparam);
	  } while (wcscmp(oldcode, codebuffer) != 0);
	  paramslist.pop_front();
	  origparam = wcstok(NULL, L",");
  }

  TCHAR* q = wcsstr(p, L")");
  wcsncpy_s(buffer, LINE_LENGTH_MAX, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  swprintf_s(buffer+(p-str), LINE_LENGTH_MAX, L"%s%s", codebuffer, q + 1);

  return buffer;
}


#pragma endregion

#pragma region Compilation
void PreProcess(FILE* inFile, FILE* outFile, boost::unordered_map<std::wstring, std::wstring>* constants, boost::unordered_map<std::wstring, std::wstring>* macros, std::list<std::wstring> currLoadedPages)
{
	TCHAR* line = (TCHAR*) calloc(sizeof(TCHAR), LINE_LENGTH_MAX);
	bool copy = TRUE;
	while(fgetws(line, LINE_LENGTH_MAX, inFile))
	{
		TCHAR* command = (TCHAR*) calloc(sizeof(TCHAR), MAX_PREPROCESS_SIZE);
		if (copy)
		{
			TCHAR* param1 = (TCHAR*) calloc(sizeof(TCHAR), MAX_PATH);
			TCHAR* param2 = (TCHAR*) calloc(sizeof(TCHAR), LINE_LENGTH_MAX);
			TCHAR* param3 = (TCHAR*) calloc(sizeof(TCHAR), wcslen(line));
			while(line[0] == ' ' || line[0] == '\t')
			{
				line = line + 1;
			}	
			if (swscanf_s(line, L"#ifndef %[^ \n]\n", param1, MAX_PATH) == 1)
			{
				if(constants->find(param1) != constants->end())
				{
					copy = FALSE;
				}
			}
			else if (swscanf_s(line, L"#ifdef %[^\n]", param1, MAX_PATH) == 1)
			{
				if(constants->find(param1) == constants->end())
				{
					copy = FALSE;
				}
			}
			else
			{
				boost::unordered_map<std::wstring, std::wstring>::iterator itr;
				for(itr = constants->begin(); itr != constants->end(); itr++)
				{
					if (macros->find(itr->first) != macros->end())
					{
						line = ReplaceMacro(line, itr->first.c_str(), itr->second.c_str(), macros->find(itr->first)->second.c_str());
					}
					else
					{
						TCHAR* oldline;
						do
						{
							oldline = line;
							line = ReplaceStr(line, itr->first.c_str(), itr->second.c_str());
						} while (wcscmp(oldline, line) != 0);
					}
				}
				if (swscanf_s(line, L"#include \"%[^\n\"]\"", param1, MAX_PATH) == 1 || swscanf_s(line, L"#include <%[^\n>]>", param1, MAX_PATH) == 1)
				{
					int oldSize = currLoadedPages.size();
					currLoadedPages.remove(param1);
					if (oldSize > (int) currLoadedPages.size())
					{
						TCHAR* error = (TCHAR*) calloc(sizeof(TCHAR), ERROR_LENGTH_MAX);
						swprintf(error, ERROR_LENGTH_MAX, CIRCULAR_REFERENCE, param1);
						MiniC::ErrorHandler::GetInstance()->RegisterError(error);
						return;
					}
					FILE* linkedFile;
					if (fwopen(&linkedFile, param1, L"r"))
					{
						TCHAR* error = (TCHAR*) calloc(sizeof(TCHAR), ERROR_LENGTH_MAX);
						swprintf(error, ERROR_LENGTH_MAX, INCLUDE_NOT_FOUND, param1);
						MiniC::ErrorHandler::GetInstance()->RegisterError(error);
						return;								
					}
					currLoadedPages.push_back(param1);
					PreProcess(linkedFile, outFile, constants, macros, currLoadedPages);
					currLoadedPages.remove(param1);
					fclose(linkedFile);
				}
				else if (swscanf_s(line, L"#define %[^\n(](%[^\n)]) %[^\n]", param1, MAX_PATH, param2, LINE_LENGTH_MAX, param3, wcslen(line)) == 3)
				{
					(*constants)[std::wstring(param1)] = std::wstring(param3);
					(*macros)[std::wstring(param1)] = std::wstring(param2);
				}
				else if (swscanf_s(line, L"#define %s %[^\n]", param1, MAX_PATH, param2, LINE_LENGTH_MAX) == 2)
				{
					(*constants)[std::wstring(param1)] = std::wstring(param2);
				}
				else if (swscanf_s(line, L"%s", param1, MAX_PATH) == 1)
				{
					if (wcscmp(param1, L"#endif") == 0)
					{
						copy = TRUE;
					}
					else if (wcscmp(param1, L"#else") == 0)
					{
						copy = !copy;
					}
					else
					{
						fwprintf(outFile, L"%s", line);
					}
				}
				else
				{

				}
				free(param1);
				free(param2);
			}
		}
		else
		{
			swscanf_s(line, L"%s", command, MAX_PREPROCESS_SIZE);			
			if (wcscmp(command, L"#endif") == 0 || wcscmp(command, L"#else") == 0)
			{
				copy = TRUE;
			}
		}
		free(command);
	}
}

bool Compile(std::wstring srcFile, bool bootload, int debug, std::wstring* output)
{
	// Files for Reading
	FILE* inFile;
	FILE* outFile;

	// Get Input File
	if (fwopen(&inFile, srcFile.c_str(), L"r") != EOK || inFile == NULL) 
	{
		TCHAR* cOutput = (TCHAR*) calloc(sizeof(TCHAR), ERROR_LENGTH_MAX);
		swprintf_s(cOutput, ERROR_LENGTH_MAX, L"%s%s%s\n", L"Couldn't find file: ", srcFile.c_str(), L". Please ensure this is pointing to the correct directory.");
		*output = std::wstring(cOutput);
		return false;
	}

	// Preprocessor
	if (MiniC::ErrorHandler::GetInstance(debug)->GetDebugCode() > 0) 
	{
		wprintf(PREPROCESSING);
	}
	int err = fwopen(&outFile, TMP_FILE, L"w");
	if (!outFile)
	{
		TCHAR* outputChar = (TCHAR*) calloc(sizeof(TCHAR), ERROR_LENGTH_MAX);
		swprintf_s(outputChar, MAX_ERROR_LEN, INVALID_INPUT_FILE, TMP_FILE, err);
		*output = std::wstring(outputChar);
		return false;
	}
	std::list<std::wstring> currLoadedFiles = std::list<std::wstring>();
	currLoadedFiles.push_back(srcFile);
	PreProcess(inFile, outFile, new boost::unordered_map<std::wstring, std::wstring>(), new boost::unordered_map<std::wstring, std::wstring>(), currLoadedFiles);
	fclose(outFile);
	if (!MiniC::ErrorHandler::GetInstance()->IsEmpty())
	{
		*output = MiniC::ErrorHandler::GetInstance()->PrintErrors();
		return false;
	}

	// Scanning and Parsing
	if (MiniC::ErrorHandler::GetInstance(debug)->GetDebugCode() > 0) 
	{
		wprintf(SCANNING);
	}
	fwopen(&outFile, TMP_FILE, L"r");
	MiniC::Scanner* scan = new MiniC::Scanner(outFile);
	MiniC::Parser* parse = new MiniC::Parser(scan);
	parse->Parse();
	fclose(outFile);

	if (parse->errors->count > 0)
	{
		return false;
	}

	// Typechecking
	MiniC::IR::AST::ProgramNode* pn = parse->program;
	MiniC::IR::AST::SymbolTable st;
	if (MiniC::ErrorHandler::GetInstance()->GetDebugCode() > 0) 
	{
		wprintf(GATHERING_FUNCTIONS);
	}
	st = pn->GetFunctions(st, bootload);
	if (!MiniC::ErrorHandler::GetInstance()->IsEmpty())
	{
		*output = MiniC::ErrorHandler::GetInstance()->PrintErrors();
		return false;
	}
	if (MiniC::ErrorHandler::GetInstance()->GetDebugCode() > 0) 
	{
		wprintf(TYPECHECKING);
	}
	st = pn->FullTypeCheck(st);
	if (!MiniC::ErrorHandler::GetInstance()->IsEmpty())
	{
		*output = MiniC::ErrorHandler::GetInstance()->PrintErrors();
		return false;
	}

	pn->Optimize(st);

	// Code Gen
	MiniC::IR::Epicness::FlowGraph::FlowGraph* fg = pn->GetFlowGraph();
	if (!MiniC::ErrorHandler::GetInstance()->IsEmpty())
	{
		*output = MiniC::ErrorHandler::GetInstance()->PrintErrors();
		return false;
	}
	fg->Optimize();
	*output = fg->GenerateCode();
	return true;
}
#pragma endregion
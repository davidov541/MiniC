#include "Compiler.h"
#include "UnitTests.h"
#include "stdafx.h"

int _tmain(int argc, TCHAR* argv[])
{ 
	// Flags Enabled
	int debug = 0;
	bool assemble = true;
	bool help = false;
	bool writeToOutput = false;
	bool assembleOnly = false;
	bool print = false;
	bool version = false;
	bool bootload = false;
	bool taskfound = false;
	bool sdCardOut = false;

	// Input and Output Values
	std::wstring asmOut;
	std::wstring coeOut;
	FILE* outFile;

	TCHAR* errMsg = (TCHAR*) calloc(sizeof(TCHAR), 1000);
	Test_SwitchStatement_TypeCheck(errMsg);
	
	/*TCHAR* test_asmOut = (TCHAR*) calloc(sizeof(TCHAR), 10000);
	Test_CompileCode(L"AbsTest.c", 10000, test_asmOut);
	*/
	// Get flags.
	if (argc == 1) 
	{
		PrintHelp();
		return 0;
	}
	else
	{
		if (ParseFlags(argv, argc, &help, &version, &writeToOutput, &assemble, &print, &assembleOnly, &bootload, &taskfound, &sdCardOut, &debug, &asmOut, &coeOut) == -1)
		{
			return -1;
		}
	}

	// Parse Flags
	std::wstring srcFile = std::wstring(argv[argc - 1]);
	if (!taskfound)
	{
		wprintf(L"%s", NO_TASK_INDICATED);
		PrintHelp();
		return 0;
	}
	else if (!print && !writeToOutput)
	{
		wprintf(L"%s", NO_OUTPUT_INDICATED);
		PrintHelp();
		return 0;
	}
	else if (help) 
	{
		PrintHelp();
		return 0;
	} 
	else if (version) 
	{
		wprintf(L"%s%s\n", VERSION_NUMBER_LABEL, VERSION_NO);
		return 0;
	} 
	else
	{
		if (!assembleOnly)
		{
			std::wstring output;
			bool compiledCorrectly = Compile(argv[argc - 1], bootload, debug, &output);
			if (!compiledCorrectly)
			{
				wprintf(L"%s", output.c_str());
			} 
			else
			{
				if (writeToOutput || assemble)
				{
					int err = fwopen(&outFile, asmOut.c_str(), L"w");
					if (outFile != NULL)
					{
						fwprintf(outFile, L"%s", output.c_str());
						fclose(outFile);
					}
					else
					{
						wprintf(INVALID_INPUT_FILE, asmOut.c_str(), err);
						return 1;
					}
				}
				if (print && !assemble)
				{
					wprintf(L"%s", output.c_str());
				}
			}
		}
		else
		{
			asmOut = std::wstring(argv[argc - 1]);
		}
		if (assembleOnly || assemble)
		{
			std::wstring command = std::wstring(L"bitepicness ");
			if (bootload)
			{
				command.append(L"-b ");
			}
			if (sdCardOut)
			{
				command.append(L"-s ");
			}
			if (print)
			{
				command.append(L"-p ");
			}
			else
			{
				command.append(L"-o ");
				command.append(coeOut.c_str());
				command.append(L" ");
			}
			command.append(asmOut.c_str());
			wsystem(command.c_str());
		}
	}
	return 0;
}
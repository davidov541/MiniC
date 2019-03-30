// WriteSDCard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WriteSDCard.h"

int main(int argc, char* argv[])
{
	if (argc == 1 || strcmp(argv[1], "-h") == 0)
	{
		wprintf(L"NAME\n");
		wprintf(L"SD Card Creator\n\n");
		wprintf(L"SYNOPSIS\n");
		wprintf(L"Creates a single binary image of an SD card from various binary program images, along with a header block which indicates the programs \
				 available on the SD card. Meant to be used with the bitepicness architecture and McOS operating system.\n\n");
		wprintf(L"SYNTAX\n");
		wprintf(L"WriteSDCard [-h] <output-file-path> (<input-file-path> <input-file-name>)*\n\n");
		wprintf(L"FLAGS\n");
		wprintf(L"%-20s%s\n", L"-h", L"Show this help document.");
		wprintf(L"NOTES\n");
		wprintf(L"Only the first 16 pairs of arguments will be inserted into the image, since the image can only support 16 programs at this point.\n");
		wprintf(L"Names must contain no spaces, or be enclosed in quotes. Only the first 14 characters of this title will be displayed.\n");
		return 1;
	}
	FileInformation programInfo[MAXNUMPROGRAMS];
	for(int i = 0; i < MAXNUMPROGRAMS; i++)
	{
		programInfo[i].content = NULL;
	}
	if (argc > MAXNUMPROGRAMS + 2)
	{
		argc = MAXNUMPROGRAMS + 2;
	}
	int numProgram = 0;
	for(int i = 2; i + 1 < argc; i += 2)
	{
		FILE* fp = fopen(argv[i], "rb");
		fseek(fp, 0, SEEK_END);
		long len = ftell(fp);
		fclose(fp);
		fp = fopen(argv[i], "rb");
		programInfo[numProgram].contentSize = len;
		programInfo[numProgram].content = (char*) calloc(sizeof(char), len + 1);
		char c = 0;
		int j = 0;
		fread(programInfo[numProgram].content, sizeof(char), len + 1, fp);
		strcpy_s(programInfo[numProgram].title, MAXTITLESIZE, argv[i + 1]);
		programInfo[numProgram].numBlocks = ceil(len / (double) NUMCHARPERBLOCK);
		fclose(fp);
		numProgram++;
	}
	int currBlock = 1;
	FILE* fp = fopen(argv[1], "wb+");
	for(int i = 0; i < MAXNUMPROGRAMS; i++)
	{
		if (programInfo[i].content == NULL)
		{
			for(int j = 0; j < MAXTITLESIZE + 2; j++)
			{
				fprintf(fp, "%c", 0);
				fprintf(fp, "%c", 0);
			}
		}
		else
		{
			for(int j = 0; j < strlen(programInfo[i].title); j++)
			{
				fprintf(fp, "%c", 0);
				fprintf(fp, "%c", programInfo[i].title[j]);
			}
			for(int j = 0; j < MAXTITLESIZE - strlen(programInfo[i].title); j++)
			{
				fprintf(fp, "%c", 0);
				fprintf(fp, "%c", 0);
			}
			fprintf(fp, "%c", 0);
			fprintf(fp, "%c", (char) currBlock);
			fprintf(fp, "%c", 0);
			fprintf(fp, "%c", (char) programInfo[i].numBlocks);
			currBlock += programInfo[i].numBlocks;
		}
	}
	for(int i = 0; i < MAXNUMPROGRAMS; i++)
	{
		if (programInfo[i].content != NULL)
		{
			fwrite(programInfo[i].content, sizeof(char), programInfo[i].contentSize, fp);
			for(int j = programInfo[i].contentSize; j < programInfo[i].numBlocks * NUMCHARPERBLOCK; j++)
			{
				fprintf(fp, "%c", 0);
			}
		}
	}
	fclose(fp);
	return 0;
}


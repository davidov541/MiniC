#ifndef __WRITESDCARD_H_
#define __WRITESDCARD_H_

#define MAXTITLESIZE 14
#define MAXNUMPROGRAMS 16
#define NUMCHARPERBLOCK 512

typedef struct 
{
	char* content;
	char title[MAXTITLESIZE];
	int numBlocks;
	long contentSize;
} FileInformation;

#endif
#define HEADER_FILE "IncludeAbsTest.h"
#include HEADER_FILE
#include <stdio.h>

int main(int argc)
{
	#ifndef A
	#define A 10
	#endif
	#ifndef Z
	#define Z 100
	#endif
	int a = abs(X);
	int b = abs(Y);
	int c = abs(Z);
	#ifdef A
	int d = abs(A);
	#endif
	#ifdef B
	int e = abs(B);
	#endif
	int f = X + Y;
	int g = Z + Z;
	putk(c);
	return 0;
}
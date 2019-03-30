#include "IncorrectIncludeAbsTest.c"

int abs(int i)
{
	int n;
	if (i > 0)
	{
		n = i;
	}
	else
	{
		n = -i;
	}
	return n;
}
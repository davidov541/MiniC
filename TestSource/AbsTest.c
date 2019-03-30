#include <stdio.h>

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

int main(int argc)
{
	int a = abs(7);
	int b = abs(-9001);
	int c = abs(42);
	putk(c);
	return 0;
}
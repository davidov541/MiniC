#include "stdio.h"

int foo(int x);

int additive = 10;

int main(int argc)
{
	int x = foo(additive);
	putk(x);
	return 0;
}

int foo(int x)
{
	return x + additive;
}
//#include <stdarg.h>
#include <stdio.h>

int foo(int x, ...)
{
	va_list ap;
	va_start(ap, x);
	int y = va_arg(ap, int);
	int z = va_arg(ap, int);
	return z;
}

int main(int argc)
{
	int a = foo(5, 10, 15, 20);
	putk(a);
	return 0;
}
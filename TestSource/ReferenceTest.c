#include <stdio.h>

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(int argc)
{
	int x = 5;
	int y = 10;
	swap(&x, &y);
	putk(x);
	return 0;
}
#include <stdio.h>

int main(int argc)
{
	int x = 5;
	int y = 10;
	int z = 15;
	int a = x + (y + z); //Returns 30
	int b = (x + x) + (y + z); //Returns 35
	int c = (x + y) + (y + (a + b + x)); //Returns 95
	putk(c);
	return 0;
}
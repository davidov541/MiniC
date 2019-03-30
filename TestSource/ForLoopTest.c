#include <stdio.h>

int main(int argc)
{
	int i = 0;
	for(i = 0; i < 10; i = i + 1)
	{
		putchar(i + 0x30);
	}
	while(true)
	{
		i = 0;
	}
	return 0;
}
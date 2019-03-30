#include <stdio.h>

int main(int argc)
{
	while(true)
	{
		int i = 0;
	}
	return 0;
}

interrupt void IH()
{
	int c = getc();
	putchar(c);
}
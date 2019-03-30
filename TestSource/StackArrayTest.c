#include <stdio.h>

int main(int argc)
{
	int arrLen = 12;
	char str[arrLen];
	str[0] = 'H';
	str[1] = 'e';
	str[2] = 'l';
	str[3] = 'l';
	str[4] = 'o';
	str[5] = ' ';
	str[6] = 'W';
	str[7] = 'o';
	str[8] = 'r';
	str[9] = 'l';
	str[10] = 'd';
	str[11] = '\0';
	int i = 0;
	char currChar = str[i];
	putchar('\n');
	putchar('\n');
	puts(str);
	while(true)
	{
		while(getchar() == i)
		{
		
		}
		i = getchar();
		if (i < arrLen)
		{
			currChar = str[i];
		}
		putchar(currChar);
	}
	return 0;
}
#include <stdio.h>

struct pair
{
	int first;
	int second;
};

int main(int argc)
{
	struct pair p = {0, 0};
	while(true)
	{
		p.second = p.first;
		p.first = getchar();
		int displayValue = p.second;
		putk(displayValue);
		//putchar(p.first);
		int currVal = getchar();
		while(currVal == p.first)
		{
			currVal = getchar();
		}
	}
	return 0;
}
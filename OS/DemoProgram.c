#include <__stdio.h>

int main(int argc)
{
	char* str = "Hello World!";
	//putchar('A');
	putchar('\n');
	putchar('\n');
	//putchar('A');
	puts(str);
	int isPressed = 0;
	while(true)
	{
		int poses;
		int posx;
		int posy;
		int constant;
		asm("rp $s0, 6;ldl $s1, -1", "", "poses:$s0,constant:$s1");
		posx = poses & constant;
		posy = poses >> 16;
		if (posx < 0x100 && posy < 0x100)
		{
			//Do nothing, since no touch was detected.
			isPressed += 1;
		}
		else
		{
			if (isPressed > 500)
			{
				if (currcolor == 7)
				{
					currcolor = 1;
					puts(str);
				}
				else
				{
					currcolor += 1;
					puts(str);
				}
				isPressed = 0;
			}			
		}
		/*else if (isPressed > 500 && posx < 0x600 && posy < 0x300)
		{
			if (currcolor != 7)
			{
				currcolor = 7;
				puts(str);
			}
			isPressed = 0;
		}
		else if (isPressed > 500 && posx < 0x600 && posy > 0x300)
		{
			if (currcolor != 4)
			{
				currcolor = 4;
				puts(str);
			}
			isPressed = 0;
		}
		else if (isPressed > 500 && posx > 0x600 && posy < 0x300)
		{
			if (currcolor != 1)
			{
				currcolor = 1;
				puts(str);
			}
			isPressed = 0;
		}
		else if (isPressed > 500)
		{
			if (currcolor != 3)
			{
				currcolor = 3;
				puts(str);
			}
			isPressed = 0;
		}*/
		int j = getk();
		poses = (posy << 16) + posx;
		putk(poses);
	}
	return 0;
}
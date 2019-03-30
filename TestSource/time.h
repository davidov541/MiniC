#ifndef __TIME_H_
#define __TIME_H_  1

void wait(int milli)
{
	asm("wp $0, 1;la $s2, T1;T1:rp $s1, 1;bne $s0, $s1, $s2;", "milli:$s0", "")
}

#endif
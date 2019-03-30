#include <__stdio.h>

interrupt void InterruptHandler()
{
	//First, get address six spaces above user program, in order to temporarily store reg values.
	asm("move $os1, $rr; ldi $os0, 1; slli $os0, 22; addi $rr, -6; sdw $os1, $rr, $0; addi $rr, 2; sdw $at, $rr, $0; addi $rr, 2;sdw $s0, $rr, $0", "", "");
	
	//Check mode. If OS, use current stack pointer. Otherwise, set stack poniter to value of $ostemp
	asm("mfc0 $os0, $mode; la $os1, OSInterrupt; beq $os0, $0, $os1;", "", "");
	
	//If it is a user program...
	asm("ldi $os1, 1;slli $os1, 22;addi $rr, -2;ldw $s0, $rr, $0; addi $rr, -2; ldw $at, $rr, $0; addi $rr, -2; ldw $rr, $rr, $0; mfc0 $os0, $ostmp; j StoreRegs", "", "");
	
	//If the OS...
	asm("OSInterrupt: ldi $os1, 1;slli $os1, 22;addi $rr, -2;ldw $s0, $rr, $0; addi $rr, -2; ldw $at, $rr, $0; addi $rr, -2; ldw $rr, $rr, $0; move $os0, $sp", "", "");
	
	//Store all registers onto new interrupt stack.
	asm("StoreRegs: sdw $sp, $os0, $0; move $sp, $os0; ldi $os0, 2; sdw $rr, $sp, $os0; addi $os0, 2; sdw $s0, $sp, $rr;", "", "");
	asm("addi $rr, 2; sdw $s1, $sp, $rr; addi $rr, 2; sdw $k0, $sp, $rr; addi $rr, 2; sdw $k1, $sp, $rr; addi $rr, 2; sdw $k2, $sp, $rr;", "", "");
	asm("addi $rr, 2; sdw $fp, $sp, $rr; addi $rr, 2; sdw $gp, $sp, $rr; addi $rr, 2; sdw $ra, $sp, $rr; addi $rr, 2; sdw $at, $sp, $rr; addi $rr, 2; sdw $v, $sp, $rr;", "", "");
	asm("addi $rr, 2; sdw $a, $sp, $rr;  addi $rr, 2; move $gp, $sp; add $sp, $rr; move $sp, $rr; move $fp, $rr", "", "");
	int cause = asm("mfc0 $v, $cause", "", "");
	if (cause == 2)
	{
		//Hardware Button Interrupt (Maybe Home?)
		asm("jr $0", "", "");
	}
	else if (cause == 4)
	{
		//SD Card Interrupt
	}
	else if (cause == 5)
	{
		//Keyboard Interrupt
		inBuffer[bufferSize] = asm("rp $v, 5", "", "");
		bufferSize += 1;
	}
	else if (cause >= 32)
	{
		//Software Interrupt
	}
	asm("addi $0, -2;ldw $a, $sp, $rr;addi $rr, -2;ldw $v, $sp, $rr;addi $rr, -2;ldw $at, $sp, $rr;addi $rr, -2;ldw $ra, $sp, $rr;addi $rr, -2;ldw $gp, $sp, $rr", "", "");
	asm("addi $0, -2;ldw $fp, $sp, $rr;addi $rr, -2;ldw $k2, $sp, $rr;addi $rr, -2;ldw $k1, $sp, $rr;addi $rr, -2;ldw $k0, $sp, $rr", "", "");
	asm("addi $0, -2;ldw $s1, $sp, $rr;addi $rr, -2;ldw $s0, $sp, $rr;add $sp, $rr;addi $rr, -4;move $sp, $rr;ldi $os0, 2;ldi $os1, 1;slli $os1, 22;move $os1, $rr;ldw $rr, $sp, $os0", "", "");
	asm("ldw $sp, $sp, $0;mfc0 $os0, $epc;eni;mtc0 $os1, $br;jr $os0", "", "");
}

int main(int argc)
{
	//Set User Program Interrupt Stack to top of Globals
	asm("mtc0 $gp, $ostmp", "", "");
	
	char* prompt = "McOS>> ";
	putchar('\n');
	putchar('\n');
	puts(prompt);
	putk(bufferSize);
	while(true)
	{
		char c = getchar();
		putchar(c);
		if (c == '\n')
		{
			puts(prompt);
		}
	}
	return 0;
}
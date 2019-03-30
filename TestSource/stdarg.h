#ifndef __STDARG_H_
#define __STDARG_H_  1
#define va_list int*

#define va_start(ap, lastarg) asm("ldi $s0, -3;lwn $s0, $fp, $s0;add $s0, $a", "", "ap:$rr")

#define va_arg(ap, type) asm("lwn $v, $s0, $0;addi $s0, 1", "ap:$s0", "ap:$rr")

#define va_end(ap) asm("ldi $s0, 0", "ap:$s0", "ap:$s0")

#endif
#ifndef __STDIO_H_
#define __STDIO_H_  1

#include <stdarg.h>

//File Output (Implemented only as dummy functions)
#define FILE void
#define EOF -1
#define size_t int
#define fpos_t int
#define stdin 1
#define stdout 2
#define stderr 3
#define FILENAME_MAX 0
#define FOPEN_MAX 0
#define TMP_MAX 0

FILE* fopen(char* filename, char* mode)
{
	return null;
}

FILE* freopen(char* filename, char* mode, FILE* stream)
{
	return null;
}

int fflush(FILE* stream)
{
	return EOF;
}

int fclose(FILE* stream)
{
	return EOF;
}

int remove(char* filename)
{
	return EOF;
}

int rename(char* oldname, char* newname)
{
	return EOF;
}

FILE* tmpfile()
{
	return null;
}

char* tmpname(char* s)
{
	return null;
}

int setvbuf(FILE* stream, char* buf, int mode, size_t size)
{
	return EOF;
}

void setbuf(FILE* stream, char* buf)
{}

int fprintf(FILE* stream, char* format, ...)
{
	return -1;
}

int vfprintf(FILE* stream, char* format, va_list arg)
{
	return -1;
}

int fscanf(FILE* stream, char* format, ...)
{
	return -1;
}

int fgetc(FILE* stream)
{
	return EOF;
}

char* fgets(char* s, int n, FILE* stream)
{
	return NULL;
}

int fputc(int c, FILE* stream)
{
	return EOF;
}

int fputs(char* s, FILE* stream)
{
	return EOF;
}

int ungetc(int c, FILE* stream)
{
	return EOF;
}

#define getc(stream) EOF

int putc(int c, FILE* stream)
{
	return EOF;
}

size_t fread(void* ptr, size_t size, size_t nobj, FILE* stream)
{
	return nobj - 1;
}

size_t fwrite(void* ptr, size_t size, size_t nobj, FILE* stream)
{
	return nobj - 1;
}

int fseek(FILE* stream, long offset, int origin)
{
	return EOF;
}

//Should return long, but no long currently in compiler.
int ftell(FILE* stream)
{
	return -1;
}


void rewind(FILE* stream)
{}

int fgetpos(FILE* stream, fpos_t* ptr)
{
	return EOF;
}

int fsetpos(FILE* stream, fpos_t* ptr)
{
	return EOF;
}

//Screen Output
int currx = -6;
int curry = 0;

#define putk(x) asm("wp $s0, 0", "x:$s0", "")

int putchar(char c)
{
	//TODO: Later, we will need to clear screen if we hit the bottom.
	//TODO: Figure out way to deal with colors.
	int intervalx = 6;
	if (currx > 255 - (intervalx << 1) || c == '\n')
	{
		// 8 pixels wide.
		currx = 0;
		curry += 10;
	}
	else
	{
		// 6 pixels wide.
		currx = currx + intervalx;
	}
	if (c != '\n')
	{
		while(asm("rp $v, 3", "", "") > 0)
		{
	
		}
		asm("ldi $k0, 512;add $k0, $s1;wp $rr, 3;ldi $k0, 1024;add $k0, $s0;wp $rr, 3;ldi $k0, 1543;wp $k0, 3;", "currx:$s1,curry:$s0", "");
		asm("ldi $s0, 2048;add $s0, $s1;wp $rr, 3", "c:$s1", "");
	}
	return c;
}

#define getchar() asm("rp $v, 2", "", "")

int puts(char* s)
{
	int i = 0;
	while(s[i] != '\0')
	{
		putchar(s[i]);
		i = i + 1;
	}
	putchar('\n');
	return 0;
}

int vprintf(char* format, va_list ap)
{
	int i = 0;
	int j = 0;
	while(format[j] != '\0')
	{
		if (format[j] == '%')
		{
			j = j + 1;
			if (format[j] == 'd')
			{
				//Use atoi here.
			}
			else if (format[j] == 's')
			{
				char* input = va_arg(ap, char*);
				int k = 0;
				while(input[k] != '\0')
				{
					putchar(input[k]);
					k = k + 1;
				}
				i = i + 1;
			}
			else if (format[j] == 'c')
			{
				char input = va_arg(ap, char);
				putchar(input);
				i = i + 1;
			}
			else if (format[j] == '%')
			{
				putchar('%');
				i = i + 1;
			}
			else if (format[j] == 'p')
			{
				//Use atoi here (or something similar for hex)		
			}
			else if (format[j] == 'o')
			{
				//Use atoi here (or something similar for octal)
			}
			else if (format[j] == 'x')
			{
				//Use atoi here (or something similar for hex)
			}
			else if (format[j] == 'u')
			{
				//Use atoi here (or something similar for unsigned)
			}
		}
		else
		{
			putchar(format[j]);
		}
		j = j + 1;
	}
	return i;
}

int printf(char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	int num = vprintf(format, ap);
	return num;
}

int scanf(char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	int i = 0;
	int j = 0;
	while(format[j] != '\0')
	{
		if (format[j] == '%')
		{
			j = j + 1;
			if (format[j] == 'd')
			{
				//Use atoi here.
			}
			else if (format[j] == 's')
			{
				char* input = va_arg(ap, char*);
				int k = 0;
				char c = getchar();
				while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
				{
					c = getchar();
				}
				while(c != ' ' && c != '\n' && c != '\t' && c != '\r')
				{
					input[k] = c;
					k = k + 1;
				}
				i = i + 1;
			}
			else if (format[j] == 'c')
			{
				char input = va_arg(ap, char);
				char c = getchar();
				while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
				{
					c = getchar();
				}
				input = c;
				i = i + 1;
			}
			else if (format[j] == '%')
			{
				char c = getchar();
				while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
				{
					c = getchar();
				}
				if (c != '%')
				{
					return i;
				}
			}
			else if (format[j] == 'p')
			{
				//Use atoi here (or something similar for hex)		
			}
			else if (format[j] == 'o')
			{
				//Use atoi here (or something similar for octal)
			}
			else if (format[j] == 'x')
			{
				//Use atoi here (or something similar for hex)
			}
			else if (format[j] == 'u')
			{
				//Use atoi here (or something similar for unsigned)
			}
		}
		else if (format[j] != ' ' && format[j] != '\n' && format[j] != '\t' && format[j] != '\r')
		{
			char c = getchar();
			while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
			{
				c = getchar();
			}
			if (c != format[j])
			{
				return i;
			}
		}
		j = j + 1;
	}
	return i;
}

//String I/O Functions
int vsprintf(char* target, char* format, va_list ap)
{	
	int i = 0;
	int j = 0;
	int k = 0;
	while(format[j] != '\0')
	{
		if (format[j] == '%')
		{
			j = j + 1;
			if (format[j] == 'd')
			{
				//Use atoi here.
			}
			else if (format[j] == 's')
			{
				char* input = va_arg(ap, char*);
				int oldk = k;
				while(input[k - oldk] != '\0')
				{
					target[k] = input[k - oldk];
					k = k + 1;
				}
				i = i + 1;
			}
			else if (format[j] == 'c')
			{
				char input = va_arg(ap, char);
				target[k] = input;
				k = k + 1;
				i = i + 1;
			}
			else if (format[j] == '%')
			{
				target[k] = '%';
				k = k + 1;
				i = i + 1;
			}
			else if (format[j] == 'p')
			{
				//Use atoi here (or something similar for hex)		
			}
			else if (format[j] == 'o')
			{
				//Use ati here (or something similar for octal)
			}
			else if (format[j] == 'x')
			{
				//Use atoi here (or something similar for hex)
			}
			else if (format[j] == 'u')
			{
				//Use atoi here (or something similar for unsigned)
			}
		}
		else
		{
			target[k] = format[j];
			k = k + 1;
		}
		j = j + 1;
	}
	return i;
}

int sprintf(char* target, char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	int num = vsprintf(target, format, ap);
	return num;
}

int sscanf(char* target, char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	int i = 0;
	int j = 0;
	int k = 0;
	while(format[j] != '\0')
	{
		if (format[j] == '%')
		{
			j = j + 1;
			if (format[j] == 'd')
			{
				//Use atoi here.
			}
			else if (format[j] == 's')
			{
				char* input = va_arg(ap, char*);
				int oldk = k;
				while (target[k] == ' ' || target[k] == '\n' || target[k] == '\t' || target[k] == '\r')
				{
					k = k + 1;
				}
				while(target[k] != ' ' && target[k] != '\n' && target[k] != '\t' && target[k] != '\r')
				{
					input[k-oldk] = target[k];
					k = k + 1;
				}
				input[k-oldk] = '\0';
				i = i + 1;
			}
			else if (format[j] == 'c')
			{
				char input = va_arg(ap, char);
				while (target[k] == ' ' || target[k] == '\n' || target[k] == '\t' || target[k] == '\r')
				{
					k = k + 1;
				}
				input = target[k];
				i = i + 1;
				k = k + 1;
			}
			else if (format[j] == '%')
			{
				while (target[k] == ' ' || target[k] == '\n' || target[k] == '\t' || target[k] == '\r')
				{
					k = k + 1;
				}
				if (target[k] != '%')
				{
					return i;
				}
				k = k + 1;
			}
			else if (format[j] == 'p')
			{
				//Use atoi here (or something similar for hex)		
			}
			else if (format[j] == 'o')
			{
				//Use atoi here (or something similar for octal)
			}
			else if (format[j] == 'x')
			{
				//Use atoi here (or something similar for hex)
			}
			else if (format[j] == 'u')
			{
				//Use atoi here (or something similar for unsigned)
			}
		}
		else if (format[j] != ' ' && format[j] != '\n' && format[j] != '\t' && format[j] != '\r')
		{
			while (target[k] == ' ' || target[k] == '\n' || target[k] == '\t' || target[k] == '\r')
			{
				k = k + 1;
			}
			if (target[k] != format[j])
			{
				return i;
			}
			k = k + 1;
		}
		j = j + 1;
	}
	return i;
}

//Error Functions
void clearerr(FILE* stream)
{}

int feof(FILE* stream)
{
	return EOF;
}

int ferror(FILE* stream)
{
	return EOF;
}

void perror(char* s)
{ }

#endif
#ifndef __CTYPE_H_
#define __CTYPE_H_ 1

int islower(char c)
{
	if (c < 97 || c > 122)
	{
		return 0;
	}
	return 1;
}

int isupper(char c)
{
	if (c < 65 || c > 90)
	{
		return 0;
	}
	return 1;
}

int isalpha(char c)
{
	return isupper(c) + islower(c);
}

int isdigit(char c)
{
	if (c < 48 || c > 57)
	{
		return 0;
	}
	return 1;
}

int isspace(char c)
{
	//Check for space, newline, carriage return, tab, formfeed or vertical tab.
	if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == 11 || c == 12)
	{
		return 1;
	}
	return 0;
}

int iscntrl(char c)
{
	if (c < 32)
	{
		return 1;
	}
	return 0;
}

int isgraph(char c)
{
	if (c > 32 && c != 127)
	{
		return 1;
	}
	return 0;
}

int isprint(char c)
{
	if (c > 31 && c != 127)
	{
		return 1;
	}
	return 0;
}

int isalnum(char c)
{
	return isalpha(c) + isdigit(c);
}

int ispunct(char c)
{
	if (isgraph(c) > 0 && isalnum(c) == 0)
	{
		return 1;
	}
	return 0;
}

int isxdigit(char c)
{
	if (isdigit(c) == 1 || (isupper(c) == 1 && c < 71) || (islower(c) == 1 && c < 103))
	{
		return 1;
	}
	return 0;
}

int tolower(int c)
{
	if (isupper(c) == 1)
	{
		return c + 32;
	}
	return c;
}

int toupper(int c)
{
	if (islower(c) == 1)
	{
		return c - 32;
	}
	return c;
}

#endif
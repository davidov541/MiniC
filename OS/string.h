#ifndef __STRING_H_
#define __STRING_H_  1

#include <stddef.h>

void* memcpy(void* dest, void* source, size_t num)
{
	for(int i = 0; i < num; i = i + 1)
	{
		dest[i] = source[i];
	}
	return dest;
}

void* memmove(void* dest, void* source, size_t num)
{
	for(int i = 0; i < num; i = i + 1)
	{
		dest[i] = source[i];
	}
	return dest;
}

char* strcpy(char* dest, char* source)
{
	int i = 0;
	while(source[i] != '\0')
	{
		dest[i] = source[i];
		i = i + 1;
	}
	dest[i] = '\0';
	return dest;
}

char* strncpy(char* dest, char* source, size_t num)
{
	bool zeros = false;
	for(int i = 0; i < num; i = i + 1)
	{
		if (zeros)
		{
			dest[i] = '\0';
		}
		else if (source[i] == '\0')
		{
			zeros = true;
			dest[i] = '\0';
		}
		else
		{
			dest[i] = source[i];
		}
	}
	if (!zeros)
	{
		dest[i] = '\0';
	}
	return dest;
}

char* strcat(char* dest, char* source)
{
	int i = 0;
	while(dest[i] != '\0')
	{
		i = i + 1;
	}
	int j = 0;
	while(source[j] != '\0')
	{
		dest[i] = source[j];
		i = i + 1;
		j = j + 1;
	}
	dest[i] = '\0';
	return dest;
}

char* strncat(char* dest, char* source, size_t num)
{
	int i = 0;
	while(dest[i] != '\0')
	{
		i = i + 1;
	}
	bool zero = false;
	for(int j = 0; j < num; j = j + 1)
	{
		if (zero)
		{
			dest[i] = '\0';
		}
		else if (source[j] == '\0')
		{
			dest[i] = '\0';
			zero = true;
		}
		else
		{
			dest[i] = source[j];
		}
		i = i + 1;
	}
	if (!zero)
	{
		dest[i] = '\0';
	}
	return dest;
}

int memcmp(void* ptr1, void* ptr2, size_t num)
{
	for(int i = 0; i < num; i = i + 1)
	{
		if (ptr1[i] != ptr2[i])
		{
			return ptr1[i] - ptr2[i];
		}
	}
	return 0;
}


int strcmp(char* ptr1, char* ptr2)
{
	int i = 0;
	while(ptr1[i] != '\0')
	{
		if (ptr1[i] != ptr2[i])
		{
			return ptr1[i] - ptr2[i];
		}
		i = i + 1;
	}
	return ptr1[i] - ptr2[i];
}

int strncmp(char* ptr1, char* ptr2, size_t num)
{
	for(int i = 0; i < num; i = i + 1)
	{
		if (ptr1[i] != ptr2[i])
		{
			return ptr1[i] - ptr2[i];
		}
	}
	return 0;
}

void* memchr(void* ptr, char value, size_t num)
{
	for(int i = 0; i < num; i = i + 1)
	{
		if (ptr[i] == value)
		{
			return ptr + i;
		}
	}
	return NULL;
}

char* strchr(char* str, char character)
{
	int i = 0;
	while(str1[i] != '\0')
	{
		if (str[i] == character)
		{
			return str + i;
		}
		i = i + 1;
	}
	return NULL;
}

size_t strcspn(char* str1, char* str2)
{
	int i = 0;
	while(str1[i] != '\0')
	{
		int j = 0;
		while(str2[j] != '\0')
		{
			if (str1[i] == str2[j])
			{
				return i;
			}
			j = j + 1;
		}
		i = i + 1;
	}
	return i;
}

char* strpbrk(char* str1, char* str2)
{
	int i = 0;
	while(str1[i] != '\0')
	{
		int j = 0;
		while(str2[j] != '\0')
		{
			if (str1[i] == str2[j])
			{
				return str1 + i;
			}
			j = j + 1;
		}
		i = i + 1;
	}
	return str1 + i;
}

char* strrchr(char* str, char character)
{
	int i = 0;
	int lastFound = 0;
	while(str1[i] != '\0')
	{
		if (str[i] == character)
		{
			lastFound = str + i;
		}
		i = i + 1;
	}
	return lastFound;
}

size_t strcspn(char* str1, char* str2)
{
	int i = 0;
	int len = 0;
	while(str1[i] != '\0')
	{
		int j = 0;
		bool found = false;
		while(str2[j] != '\0')
		{
			if (str1[i] == str2[j])
			{
				found = true;
			}
			j = j + 1;
		}
		if (found)
		{
			len = len + 1;
		}
		else if (len > 0)
		{
			return len;
		}
		i = i + 1;
	}
	return 0;
}

char* strstr(char* str1, char* str2)
{
	int i = 0;
	while(str1[i] != '\0')
	{
		int j = 0;
		int k = i;
		while(str1[k] == str2[j])
		{
			j = j + 1;
			k = k + 1;
		}
		if (str2[j] == '\0')
		{
			return str1 + i;
		}
		i = i + 1;
	}
	return NULL;
}

void* memset(void* ptr, char value, size_t num)
{
	for(int i = 0; i < num; i = i + 1)
	{
		ptr[i] = value;
	}
	return ptr;
}

//Not yet implemented due to no constant strings or error messages yet.
char* strerror(int errnum)
{
	return NULL;
}

char* currTokenizedString = NULL;

char* strtok(char* str, char* delim)
{
	char* currStr;
	if (str == NULL)
	{
		currStr = currTokenizedString;
	}
	else 
	{
		currStr = str;
		int i = 0;
		bool found = true;
		while(currStr[i] != '\0' && found)
		{
			int j = 0;
			found = false;
			while(delim[j] != '\0')
			{
				if (currStr[i] == delim[j])
				{
					currStr = currStr + 1;
					found = true;
					break;
				}
				j = j + 1;
			}
		}
	}
	int i = 0;
	while(currStr[i] != '\0')
	{
		int j = 0;
		while(delim[j] != '\0')
		{
			if (currStr[i] == delim[j])
			{
				char* returnable = currStr;
				currStr = currStr + i + 1;
				currStr[i] = '\0';
				return returnable;
			}
			j = j + 1;
		}
	}
	return NULL;
}

int strlen(char* str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		i = i + 1;
	}
	return i;
}

#endif
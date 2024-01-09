#include "shell.h"

/**
 **_strncpy - copy string function
 *@dest: destination string (1st str)
 *@src: source string (2nd str)
 *@n: used as an increment count towards chars to be copied
 *Return: values of type char
 */
char *_strncpy(char *dest, char *src, int n)
{
	char *new_str = dest;
	int a = 0, b;

	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (new_str); /* return (dest) */
}

/**
 **_strncat - concatenates two strings
 *@dest: destination string (1st str)
 *@src: source string (2nd str)
 *@n: represents the amount of bytes to be allocated
 *Return: values of type char (concatenated string)
 */
char *_strncat(char *dest, char *src, int n)
{
	int s = 0, t = 0;
	char *new = dest;

	while (dest[s] != '\0')
		s++;
	while (src[t] != '\0' && t < n)
	{
		dest[s] = src[t];
		s++;
		t++;
	}
	if (t < n)
		dest[s] = '\0';
	return (new);
}

/**
 **_strchr - Identify a character within a string
 *@s: string to be computed
 *@c: character to locate
 *Return: pointer to memory area
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

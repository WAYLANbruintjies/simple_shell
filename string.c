#include "shell.h"

/**
 * _strlen - Output the length of (*s) string
 * @s: string to be computed
 * Return: string length
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (*s++) /* while string is not empty */
		len++;
	return (len);
}

/**
 * _strcat - Concatenates two strings
 * @dest: destination (buf)
 * @src: source (buf)
 * Return: type char pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	char *add;

	add = dest;

	while (*dest) /* dest == TRUE || dest != NULL */
		dest++;
	while (*src) /* same for source */
		*dest++ = *src++;
	*dest = *src;
	return (add);
}

/**
 * _strcmp - Compares two strangs with each other
 * @s1: first string
 * @s2: second string
 * Return: 1 (s1 > s2) , -1 (s1 < s2), 0 (s1 == s2)
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2) /* s1 AND s2 == TRUE || s1 AND s2 != NULL */
	{
		if (*s1 != *s2) /* if s1 AND s2 are two diff strings */
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);

	/* ternary operator as shorthand to if, else statement */
	return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Check to see if @needle starts with @haystack
 * @haystack: string 1
 * @needle: string 2
 * Return: pointer to haystack address, or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

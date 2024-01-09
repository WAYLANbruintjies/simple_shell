#include "shell.h"

/**
 * _putchar - Puts character c to standard output (stdout)
 * @c: character to be computed
 * Return: 1 (Success), -1 (Failure)
 */
int _putchar(char c)
{
	static int num;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || num >= WRITE_BUF_SIZE)
	{
		write(1, buffer, num);
		num = 0;
	}
	if (c != BUF_FLUSH) /* failure on process */
		buffer[num++] = c;
	return (1); /* error code returned */
}

/**
 * _puts - Puts a string
 * @str: string to be computed
 * Return: void
 */
void _puts(char *str)
{
	int n = 0;

	/* empty string *//* (!str) */
	if (str == NULL)
		return;
	while (str[n] != '\0')
	{
		n++;
		_putchar(str[n]);
	}
}

/**
 * _strcpy - Copies a string
 * @dest: destination
 * @src: source
 * Return: a pointer to dest (copied str)
 */
char *_strcpy(char *dest, char *src)
{
	int n = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[n]) /* src != NULL */
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: string to be duplicated
 * Return: duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *dup_str;

	if (!str)
		return (NULL);
	while (*str++)
		len++;

	dup_str = malloc(sizeof(char) * (len + 1));
	if (!dup_str) /* if string is empty */
		return (NULL);
	for (len++; len--;)
		dup_str[len] = *--str;
	return (dup_str);
}

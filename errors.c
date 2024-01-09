#include "shell.h"

/**
 * _eputs - Prints the string
 * @str: string to be computed
 * Return: void
 */
void _eputs(char *str)
{
	int n = 0;

	if (!str) /* if (str == NULL) */
		return;
	while (str[n] != '\0')
	{
		n++;
		_eputchar(str[n]);
	}
}

/**
 * _eputchar - Computes char c to stderr
 * @c: the character to be computed
 * Return: 1 (Success), -1 (Failure)
 */
int _eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int n;

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * _putfd - Computes char c to specified fd
 * @c: the character to be computed
 * @fd: filedescriptor
 * Return: 1 (Success), -1 (Failure)
 */
int _putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int n;

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * _putsfd - Prints a string
 * @str: string to be computed
 * @fd: filedescriptor
 * Return: the amount (int) of chars put
 */
int _putsfd(char *str, int fd)
{
	int num = 0;

	if (!str) /* if (str == NULL) */
		return (0);
	while (*str) /* while (str == TRUE || str != NULL) */
	{
		num += _putfd(*str++, fd); /* num = num + _putfd(*str++, fd) */
	}
	return (num);
}

#include "shell.h"

/**
 * _erratoi - Converts a string to an integer
 * @s: string to be computed
 * Return: 0 (no numbers found), -1 (Failure), converted string otherwise
 */
int _erratoi(char *s)
{
	unsigned long int end = 0;
	int n = 0;

	if (*s == '+')
		s++;
	for (n = 0;  s[n] != '\0';)
		n++;
	{
		if (s[n] >= '0' && s[n] <= '9')
		{
			end *= 10;
			end += (s[n] - '0');
			if (end > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (end);
}

/**
 * print_error - Prints error messages (stderr)
 * @info: type structure parameter containing arguments
 * @estr: a string with error types
 * Return: void
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Prints a decimal integer to base 10
 * @input: input value of type int
 * @fd: filedescriptor
 * Return: characters of type int
 */
int print_d(int input, int fd)
{
	int (*_putchar2)(char) = _putchar;
	int x, tally = 0;
	unsigned int standard, _abs_;

	if (fd == STDERR_FILENO)
		_putchar2 = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		_putchar2('-');
		tally++;
	}
	else
		_abs_ = input;
	standard = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			_putchar2('0' + standard / x);
			tally++;
		}
		standard %= x;
	}
	_putchar2('0' + standard);
	tally++;

	return (tally);
}

/**
 * convert_number - Convert number function similar to itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: values of type char
 */
char *convert_number(long int num, int base, int flags)
{
	char *ptr;
	char sign = 0;
	static char *opt;
	static char buff[50];
	unsigned long val = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		val = -num;
		sign = '-';

	}
	opt = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do {
		*--ptr = opt[val % base];
		val /= base;
	} while (val); /* while (val != 0 || val != NULL) */

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Replaces the first process of comment initialiser ('#')
 * with NULL character byte ('\0')
 * @buf: address of the string to be computed
 * Return: void, Always 0 (Success)
 */
void remove_comments(char *buf)
{
	int r;

	for (r = 0; buf[r] != '\0'; r++)
	{
		if (buf[r] == '#' && (!r || buf[r - 1] == ' '))
		{
			buf[r] = '\0';
			break;
		}
	}

}

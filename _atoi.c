#include "shell.h"

/**
 * interactive - Returns true if shell is in interactive mode
 * @info: struct address (pointer)
 * Return: 1 for Interactive Mode, otherwise 0
 */
int interactive(info_t *info)
{
        return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the character to be computed
 * @delim: delimeter string
 * Return: 1 (True), 0 (False)
 */
int is_delim(char c, char *delim)
{
        while (*delim)
                if (*delim++ == c)
                        return (1);
        return (0);
}

/**
 * _isalpha - checks for alphabetic characters
 * @c: The character to be computed
 * Return: 1 if char c is alphabetic, otherwise 0
 */
int _isalpha(int c)
{
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                return (1);
        else
                return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: string to be converted
 * Return: 0 (No num in string), converted number otherwise
 */
int _atoi(char *s)
{
	int n, sign = 1, flag = 0, out;
	unsigned int yield = 0;

	for (n = 0; s[n] != '\0' && flag != 2; n++)
	{
		if (s[n] == '-')
			sign *= -1;

		if (s[n] >= '0' && s[n] <= '9')
		{
			flag = 1;
			yield *= 10;
			yield += (s[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		out = -yield;
	else
		out = yield;

	return (out);
}

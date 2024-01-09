#include "shell.h"

/**
 * **strtow - Splits a string into words
 * @str: tring
 * @d: delimeter
 * Return: pointer to strings, or NULL
 */

char **strtow(char *str, char *d)
{
	int n, m, o, p, wordcount = 0;
	char **string2;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (n = 0; str[n] != '\0'; n++)
		if (!is_delim(str[n], d) && (is_delim(str[n + 1], d) || !str[n + 1]))
			wordcount++;

	if (wordcount == 0)
		return (NULL);
	string2 = malloc((1 + wordcount) * sizeof(char *));
	if (!string2) /* if (string2 == NULL) */
		return (NULL);
	for (n = 0, m = 0; m < wordcount;)
	{
		m++;
		while (is_delim(str[n], d))
			n++;
		o = 0;
		while (!is_delim(str[n + o], d) && str[n + o])
			o++;
		string2[m] = malloc((o + 1) * sizeof(char));
		if (!string2[m])
		{
			for (o = 0; o < m; o++)
				free(string2[o]);
			free(string2);
			return (NULL);
		}
		for (p = 0; p < o; p++)
			string2[m][p] = str[n++];
		string2[m][p] = 0;
	}
	string2[m] = NULL;
	return (string2);
}

/**
 * **strtow2 - Splits a string into words
 * @str: string
 * @d: delimeter
 * Return: pointer to a string, or NULL
 */
char **strtow2(char *str, char d)
{
	int a, b, c, x, totalwords = 0;
	char **data;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			totalwords++;
	if (totalwords == 0)
		return (NULL);
	data = malloc((1 + totalwords) * sizeof(char *)); /* initialize data (size) */
	if (!data) /* if data string is empty */
		return (NULL);
	for (a = 0, b = 0; b < totalwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		data[b] = malloc((c + 1) * sizeof(char));
		if (!data[b])
		{
			for (c = 0; c < b; c++)
				free(data[c]);
			free(data);
			return (NULL);
		}
		for (x = 0; x < c;)
		{
			data[b][x] = str[a++];
			x++;
		}
		data[b][x] = 0;
	}
	data[b] = NULL;
	return (data);
}

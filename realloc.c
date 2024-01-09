#include "shell.h"

/**
 * _memset - Sets memory with a constant
 * @s: pointer to memory area
 * @b: fills ponter (*s) in value
 * @n: number of bytes to be set
 * Return: pointer to memory area (char *s)
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}

/**
 * ffree - Frees a double pointer string
 * @pp: double pointer string
 * Return: void
 */
void ffree(char **pp)
{
	char **ptr = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(ptr);
}

/**
 * _realloc - Re-allocates a memory block
 * @ptr: pointer to the old memset block
 * @old_size: size of old block
 * @new_size: size of new block
 * Return: pointer to the previous (old) block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *c;

	if (!ptr) /* if (ptr == NULL) */
		return (malloc(new_size));
	if (!new_size) /* if (new_size == NULL) */
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	c = malloc(new_size);
	if (!c)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		c[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (c);
}

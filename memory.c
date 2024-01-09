#include "shell.h"

/**
 * bfree - NULLs the address and frees a pointer
 * @ptr: address pointer (ptr) to free
 * Return: 1 (Success), 0 (Failure)
 */
int bfree(void **ptr)
{
	if (ptr && *ptr) /* ptr is a double pointer */
	{
		free(*ptr);
		*ptr = NULL; /* Makes sure the pointer is empty */
		return (1);
	}
	return (0);
}

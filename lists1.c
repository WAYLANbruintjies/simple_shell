#include "shell.h"

/**
 * print_list - Print all elements of a linked list
 * @h: pointer to head of the node
 * Return: size of the node/list
 */
size_t print_list(const list_t *h)
{
	size_t n  = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * list_len - Computes the length of a linked list
 * @h: pointer to head of the node
 * Return: size of the node/list
 */
size_t list_len(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * list_to_strings - Prints an array of strings
 * @head: pointer to the head node
 * Return: values of type char
 */
char **list_to_strings(list_t *head)
{
	list_t *tab = head;
	char **arr_str;
	char *str;
	size_t n = list_len(head), m;

	if (!head || !n)
		return (NULL);
	arr_str = malloc(sizeof(char *) * (n + 1));
	if (!arr_str)
		return (NULL);
	for (n = 0; tab; tab = tab->next, n++)
	{
		str = malloc(_strlen(tab->str) + 1);
		if (!str)
		{
			for (m = 0; m < n; m++)
				free(arr_str[m]);
			free(arr_str);
			return (NULL);
		}

		str = _strcpy(str, tab->str);
		arr_str[n] = str;
	}
	arr_str[n] = NULL;
	return (arr_str);
}

/**
 * node_starts_with - Outputs a node string beginning with a prefix
 * @node: pointer to the address of the first part of the node
 * @prefix: string to be computed
 * @c: second character to identify
 * Return: valid node or NULL
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);

		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head) /* head == TRUE || head != NULL */
	{
		if (head == node)
			return (n);

		head = head->next;
		n++;
	}
	return (-1);
}

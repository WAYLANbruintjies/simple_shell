#include "shell.h"

/**
 * _myhistory - Displays the history list, one command per line
 * line numbers begin at 0 before each command
 * @info: type structure containing arguments
 *  Return: Always 0 (Success)
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Sets alias to string
 * @info: type parameter struct (pointer)
 * @str: string alias to be computed
 * Return: Always 0 (Success), 1 (Failure)
 */
int unset_alias(info_t *info, char *str)
{
	char *a, b;
	int out;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	out = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*a = b;
	return (out);
}

/**
 * set_alias - Sets alias to a string
 * @info: type parameter struct (pointer)
 * @str: string alias to be computed
 * Return: Always 0 (Success), 1 (Failure)
 */
int set_alias(info_t *info, char *str)
{
	char *a;

	a = _strchr(str, '=');
	if (!a) /* if (a == NULL) */
		return (1);
	if (!*++a)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string
 * @node: node of alias
 * Return: Always 0 (Success), 1 (Failure)
 */
int print_alias(list_t *node)
{
	char *b = NULL;
	char *a = NULL;

	if (node) /* if (node != NULL || 0 */
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Copies the authentic builtin alias (man alias)
 * @info: type structure containing arguments
 * Return: Always 0 (Success)
 */
int _myalias(info_t *info)
{
	list_t *listnode = NULL;
	int n = 0;
	char *a = NULL;

	if (info->argc == 1)
	{
		listnode = info->alias;
		while (listnode) /* while (listnode  == True || listnode != NULL */
		{
			print_alias(listnode);
			listnode = listnode->next;
		}
		return (0);
	}
	for (n = 1; info->argv[n]; n++)
	{
		a = _strchr(info->argv[n], '=');
		if (a)
			set_alias(info, info->argv[n]);
		else
			print_alias(node_starts_with(info->alias, info->argv[n], '='));
	}

	return (0);
}

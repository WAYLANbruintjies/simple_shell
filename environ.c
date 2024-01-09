#include "shell.h"

/**
 * _myenv - Prints the present environment
 * @info: type structure containing arguments
 * Return: Always 0 (Success)
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - fetch the value of an environ variable
 * @info: type structure containing arguments (pointer)
 * @name: variable name
 * Return: values of type char
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *listnode = info->env;
	char *a;

	while (listnode) /* while (listnode == TRUE || listnode != NULL) */
	{
		a = starts_with(listnode->str, name);
		if (a && *a)
			return (a);
		listnode = listnode->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialise new environment variables
 * OR modify existing vars
 * @info: type structure containing arguments
 * Return: Always 0 (Success)
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: type structure containing arguments
 * Return: Always 0 (Success)
 */
int _myunsetenv(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("Not enough arguements!\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);

	return (0);
}

/**
 * populate_env_list - Inhabits env linked list
 * @info: type structure containing arguments
 * Return: Always 0 (Success)
 */
int populate_env_list(info_t *info)
{
	size_t n;
	list_t *listnode = NULL;

	for (n = 0; environ[n]; n++)
		add_node_end(&listnode, environ[n], 0);
	info->env = listnode;
	return (0);
}

#include "shell.h"

/**
 * _setenv - Load a new environment variable, modify an existing one
 * @info: type parameter structure with arguments
 * @var: pointer to string1
 * @value: pointer to string2
 *  Return: Always 0 (Success)
 */
int _setenv(info_t *info, char *var, char *value)
{
	list_t *log;
	char *ptr;
	char *buff_init = NULL;

	if (!var || !value) /* if var AND value == NULL */
		return (0);

	buff_init = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff_init)
		return (1);
	_strcpy(buff_init, var);
	_strcat(buff_init, value);
	_strcat(buff_init, "=");
	log = info->env;
	while (log)
	{
		ptr = starts_with(log->str, var);
		if (ptr && *ptr == '=')
		{
			free(log->str);
			log->str = buff_init;
			info->env_changed = 1;
			return (0);
		}
		log = log->next;
	}

	add_node_end(&(info->env), buff_init, 0);
	free(buff_init);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: type parameter structure with arguments
 * @var: pointer to a string to be removed
 * Return: 1 (Success), 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	size_t n = 0;
	char *c;
	list_t *node_list = info->env;

	if (!node_list || !var)
		return (0);

	while (node_list)
	{
		c = starts_with(node_list->str, var);
		if (c && *c == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), n);
			n = 0;
			node_list = info->env;
			continue;
		}
		n++;
		node_list = node_list->next;
	}
	return (info->env_changed);
}

/**
 * get_environ - Get an environment variable
 * @info: type parameter structure with arguments
 * Return: Always 0 (Success)
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

#include "shell.h"

/**
 * is_chain - Tests for a chain delimeter
 * @info: type parameter structure
 * @buf: buffer
 * @p: pointer to an address in buffer
 * Return: 1 (Success), 0 (Failure)
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t vol = *p;

	if (buf[vol] == '|' && buf[vol + 1] == '|') /* OR operator */
	{
		buf[vol] = 0;
		vol++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[vol] == '&' && buf[vol + 1] == '&') /* AND operator */
	{
		buf[vol] = 0;
		vol++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[vol] == ';') /* end of command */
	{
		buf[vol] = 0; /* substitute semicolon with NULL */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = vol;
	return (1);
}

/**
 * check_chain - Evaluates ongoing chaining based on prev status
 * @info: type parameter structure
 * @buf: buffer
 * @p: pointer to an address in buffer
 * @i: starting index in buffer
 * @len: length varable
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}

	*p = x;
}

/**
 * replace_vars - Replace vars within a 'tokenized' str
 * @info: type parameter structure
 * Return: 1 (Success), 0 (Failure)
 */
int replace_vars(info_t *info)
{
	list_t *add_node;
	int inc = 0;

	for (inc = 0; info->argv[inc]; inc++) /* increment ++ */
	{
		if (info->argv[inc][0] != '$' || !info->argv[inc][1])
			continue;

		if (!_strcmp(info->argv[inc], "$?"))
		{
			replace_string(&(info->argv[inc]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[inc], "$$"))
		{
			replace_string(&(info->argv[inc]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		add_node = node_starts_with(info->env, &info->argv[inc][1], '=');
		if (add_node)
		{
			replace_string(&(info->argv[inc]),
					_strdup(_strchr(add_node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[inc], _strdup(""));

	}
	return (0);
}

/**
 * replace_alias - Replaces an alias within a tokenized str
 * @info: type parameter structure
 * Return: 1 (Success), 0 (Failure)
 */
int replace_alias(info_t *info)
{
	list_t *log;
	int n;
	char *ptr;

	for (n = 0; n < 10; n++)
	{
		log = node_starts_with(info->alias, info->argv[0], '=');
		if (!log) /* if (log == NULL) */
			return (0);
		free(info->argv[0]);
		ptr = _strchr(log->str, '=');
		if (!ptr) /* if ptr is empty */
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_string - Replace a string
 * @old: old string
 * @new: new string
 * Return: 1 (Success), 0 (Failure)
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new; /* string replaced with new */
	return (1);
}

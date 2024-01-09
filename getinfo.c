#include "shell.h"

/**
 * set_info -Sets info_t struct called info
 * @info: type parameter structure
 * @argv: argument vector
 */
void set_info(info_t *info, char **argv)
{
	int n = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (n = 0; info->argv && info->argv[n];)
			n++;

		info->argc = n;

		replace_vars(info);
		replace_alias(info);
	}
}

/**
 * free_info - Frees the info_t struct
 * @info: type parameter structure
 * @all: only valid/true if all fields are freed
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->path = NULL;
	info->argv = NULL;

	if (all)
	{
		if (info->alias)
			free_list(&(info->alias));
		if (info->env)
			free_list(&(info->env));
		ffree(info->environ);
			info->environ = NULL;
		if (!info->cmd_buf)
			free(info->arg);
		bfree((void **)info->cmd_buf);
		if (info->history)
			free_list(&(info->history));
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * clear_info - Clears info_t struct named info
 * @info: type parameter structure
 */
void clear_info(info_t *info)
{
	info->argc = 0;
	info->argv = NULL;
	info->arg = NULL;
	info->path = NULL;
}

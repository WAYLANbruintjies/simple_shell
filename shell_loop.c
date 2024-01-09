#include "shell.h"

/**
 * hsh - Shell loop
 * @info: type parameter structure
 * @argv: argument vector
 * Return: 0 (Success,) 1 (Failure), or error code
 */
int hsh(info_t *info, char **argv)
{
	ssize_t n = 0;
	int loop = 0;

	while (n != -1 && loop != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		n = get_input(info);
		if (n != -1)
		{
			set_info(info, argv);
			loop = find_builtin(info);
			if (loop == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');

		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);
	if (loop == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num); /* return error */
	}
	return (loop);
}

/**
 * find_builtin - Finds builtin commands
 * @info: type parameter structure
 * Return: 0 Always (Success), -1 (Failure),
 * 1 (found but not successful),
 * 2 (signals exit())
 */
int find_builtin(info_t *info)
{
	int n, builtin_r = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (n = 0; builtintbl[n].type; n++)
		if (_strcmp(info->argv[0], builtintbl[n].type) == 0)
		{
			info->line_count++;
			builtin_r = builtintbl[n].func(info);
			break;
		}

	return (builtin_r);
}

/**
 * find_cmd - Search and locates a cmd command in PATH
 * @info: type parameter structure
 * Return: void
 */
void find_cmd(info_t *info)
{
	int a, b;
	char *path;

	path = NULL;
	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, b = 0; info->arg[a];)
		a++;
	if (!is_delim(info->arg[a], " \t\n"))
		b++;
	if (!b) /* if (b == NULL */
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an executable thread in order to run cmd command
 * @info: type parameter structure
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child;

	child = fork(); /* fork function called */
	if (child == -1)
	{
		perror("Error:"); /* FIXME: PUT ERROR FUNCTION */
		return;
	}
	if (child == 0) /* NULL */
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

#include "shell.h"

/**
 * is_cmd - Tests a file to see whether it is an executable
 * @info: type parameter structure
 * @path: file path
 * Return: 1 (Success), 0 (Failure)
 */
int is_cmd(info_t *info, char *path)
{
	struct stat est;

	(void)info;
	if (path == NULL || stat(path, &est))
		return (0);

	if (est.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * find_path - Search for the cmd command in the 'PATH' string
 * @info: type parameter struct called info
 * @pathstr: a 'PATH' string within the func
 * @cmd: the cmd  command to locate
 * Return: values of type char (the cmd path) or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int n = 0, index = 0;
	char *trace;

	if (!pathstr) /* if ((pathstr == NULL) */
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[n] || pathstr[n] == ':')
		{
			trace = dup_chars(pathstr, index, n);
			if (!*trace) /* if (trace == NULL */
				_strcat(trace, cmd);
			else
			{
				_strcat(trace, "/");
				_strcat(trace, cmd);
			}
			if (is_cmd(info, trace))
				return (trace);
			if (!pathstr[n])
				break;
			index = n;
		}
		n++;
	}
	return (NULL);
}

/**
 * dup_chars - Duplicates characters
 * @pathstr: a 'PATH' string
 * @start: start
 * @stop: stop
 * Return: buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	int i = 0, n = 0;
	static char buffer[1024];

	for (n = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[n++] = pathstr[i];

	buffer[n] = 0;
	return (buffer);
}

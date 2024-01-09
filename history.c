#include "shell.h"

/**
 * get_history_file - Gets the history/previous file
 * @info: type parameter structure
 * Return: the history file in string format
 */

char *get_history_file(info_t *info)
{
	char *buff, *fdir;

	fdir = _getenv(info, "HOME=");
	if (fdir == NULL) /* if (!fdir) */
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(fdir) + _strlen(HIST_FILE) + 2));
	if (buff == NULL)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, fdir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * read_history - Reads file history
 * @info: type parameter structure
 * Return: histcount, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, nth = 0, numline = 0;
	char *buffer = NULL;
	char *fname = get_history_file(info);
	ssize_t fd, rd_len, unit = 0;
	struct stat st;

	if (fname == NULL) /* if (!fname) */
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		unit = st.st_size;
	if (unit < 2)
		return (0);
	buffer = malloc(sizeof(char) * (unit + 1));
	if (buffer == 0)
		return (0);
	rd_len = read(fd, buffer, unit);
	buffer[unit] = 0;
	if (rd_len <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < unit; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(info, buffer + nth, numline++);
			nth = i + 1;
		}
	if (nth != i)
		build_history_list(info, buffer + nth, numline++);
	free(buffer);
	info->histcount = numline;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * write_history - Creates a new file and adds to an existing old file
 * @info: type parameter structure
 * Return: 1 (Success), -1 (Failure)
 */
int write_history(info_t *info)
{
	list_t *tab;
	ssize_t fd;
	char *fname = get_history_file(info);

	tab = NULL;
	if (!fname) /* if fname == 0 */
		return (-1); /* Failed func */

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644); /* casting fd */
	free(fname);
	if (fd == -1)
		return (-1); /* Fail */

	for (tab = info->history; tab; tab = tab->next)
	{
		_putsfd(tab->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd); /* Close filedescriptor */
	return (1); /* Success */
}

/**
 * build_history_list - Creates an addition entry to a history node
 * @info: type parameter structure
 * @buf: file buffer
 * @linecount: amount of lines priviously counted (histcount)
 * Return: Always 0 (Success)
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *newnode = NULL;

	if (info->history)
		newnode = info->history;
	add_node_end(&newnode, buf, linecount);

	if (!info->history)
		info->history = newnode;
	return (0);
}

/**
 * renumber_history - Renumbers the history node after changes implemented
 * @info: type parameter structure
 * Return: the new modified histcount after changes occured
 */
int renumber_history(info_t *info)
{
	int n = 0;
	list_t *log = info->history;

	while (log) /* log is TRUE || log != NULL */
	{
		log = log->next;
		log->num = n++;
	}
	return (info->histcount = n);
}

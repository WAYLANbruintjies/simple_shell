#include "shell.h"

/**
 * input_buf - Buffers commands chained
 * @info: type parameter structure
 * @buf: pointer to buffer address
 * @len: pointer to len variable address
 * Return: byte values
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	size_t size = 0;
	ssize_t rd = 0;

	if (!*len) /* Fill the buffer with data if empty */
	{
		/* bfree((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rd = getline(buf, &size, stdin);
#else
		rd = _getline(info, buf, &size);
#endif
		if (rd > 0)
		{
			if ((*buf)[rd - 1] == '\n')
			{
				(*buf)[rd - 1] = '\0';
				rd--;
			}
			remove_comments(*buf);
			info->linecount_flag = 1;
			build_history_list(info, *buf, info->histcount++);
			{
				info->cmd_buf = buf;
				*len = rd;
			}
		}
	}
	return (rd);
}

/**
 * read_buf - Reads the buffer
 * @info: type parameter structure
 * @buf: buffer
 * @i: size of buffer
 * Return: variable rd
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t rd = 0;

	if (*i) /* If (*i == TRUE || *i != NULL */
		return (0);
	rd = read(info->readfd, buf, READ_BUF_SIZE);
	if (rd >= 0)
		*i = rd;
	return (rd);
}

/**
 * get_input - Obtains a line excluding the new line
 * @info: type parameter structure
 * Return: computed bytes read
 */
ssize_t get_input(info_t *info)
{
	ssize_t rd = 0;
	char **buf_live = &(info->arg), *current;
	static char *buf;
	static size_t x, field, y;

	_putchar(BUF_FLUSH);
	rd = input_buf(info, &buf, &field);
	if (rd == -1) /* End Of File (EOF) */
		return (-1);
	if (field) /* Not empty, still commands left in buf_p */
	{
		y = x; /* New iterator */
		current = buf + x; /* Allow pointer for return */

		check_chain(info, buf, &y, x, field);
		while (y < field) /* Iterator in use */
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1; /* Increment */
		if (x >= field)
		{
			x = field = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_live = current; /* Reverb pointer to current command position */
		return (_strlen(current)); /* Return length of current command */
	}

	*buf_live = buf; /* Reset buffer from _getline() */
	return (rd); /* Return buffer length from _getline() */
}

/**
 * _getline - Gets the next line of input (STDIN)
 * @info: type parameter structure
 * @ptr: pointer to buffer address
 * @length: size of the buffer
 * Return: string
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	size_t n;
	ssize_t rd = 0, str = 0;
	static size_t i, span;
	static char buf[READ_BUF_SIZE];
	char *p1 = NULL, *p2 = NULL, *c;

	p1 = *ptr;
	if (p1 && length)
		str = *length;
	if (i == span)
		i = span = 0;

	rd = read_buf(info, buf, length);
	if (rd == -1 || (rd == 0 && span == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	n = c ? 1 + (unsigned int)(c - buf) : span;
	p2 = _realloc(p1, str, str ? str + n : n + 1);
	if (!p2) /* MALLOC FAIL ! */
		return (p1 ? free(p1), -1 : -1);

	if (str)
		_strncat(p2, buf + i, n - i);
	else
		_strncpy(p2, buf + i, n - i + 1);

	str += n - i; /* str = str + (n - i) */
	i = n;
	p1 = p2;

	if (length)
		*length = str;
	*ptr = p1;
	return (str);
}

/**
 * sigintHandler - Blocks the use of ctrl-C
 * @sig_num: signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

#include "shell.h"

/**
 * _myexit - Exits the shell programme
 * @info: type parameter structure
 * Return: displays  given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If exit arg is TRUE */
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Changes current directory of a process
 * @info: a structure pointer containing arguments
 * Return: Always 0 (Success)
 */
int _mycd(info_t *info)
{
	char *s, *dir, buff[1024];
	int ch_direc;

	s = getcwd(buff, 1024);
	if (s == NULL) /* if (!s) */
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir) /* if (dir == NULL) */
			ch_direc = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			ch_direc = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}

		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ch_direc = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_direc = chdir(info->argv[1]);
	if (ch_direc == -1)
	{
		print_error(info, "cannot cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - Change current dir of the instance
 * @info: type parameter structure
 * Return: Always 0 (Success)
 */
int _myhelp(info_t *info)
{
	char **arguments;

	arguments = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arguments);
	return (0);
}

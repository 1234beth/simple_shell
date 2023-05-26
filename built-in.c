/*task 5*/
#include "shell.h"

/**
 * _exit - exits the shell
 * @info: Structure with args
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _exit(info_t *info)
{
	int xlook;

	if (info->argv[1])
	{
		xlook = _erratoi(info->argv[1]);
		if (xlook == -1)
		{
			info->status = 2;
			print_error(info, "not allowed no : ");
			_puts(info->argv[1]);
			_putchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the current directory of the process
 * @info: Structure with args
 * Return: Always 0
 */
int _cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("Hey: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* Hey: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
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
		chdir_ret = /* Hey: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - help
 * @info: Structure withargs
 * Return: Always 0
 */
int _help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("in order \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

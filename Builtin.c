#include "shell.h"

/**
 * exit_shell - Exits the shell with a specified exit status.
 * @info: Pointer to a struct containing shell information.
 *
 * Return: Returns -2 after setting the exit status based on the argument.
 *         If no argument is provided, it sets the exit status to -1.
 */
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_status = _strtoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_status;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Changes the current directory of the shell process.
 * @info: Pointer to a struct containing shell information.
 *
 * Return: Always returns 0.
 */
int change_directory(info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: Handle getcwd failure here\n");
	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			chdir_result = chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_result = chdir(target_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
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
 * help_shell - Displays help information for the shell.
 * @info: Pointer to a struct containing shell information.
 *
 * Return: Always returns 0.
 */
int help_shell(info_t *info)
{
	char **arguments;

	arguments = info->argv;
	_puts("Help: This function is not yet implemented.\n");
	if (0)
		_puts(*arguments);
	return (0);
}

#include "shell.h"

/**
 * _myexit2 - Exits the shell.
 * @info: Pointer to a structure containing potential arguments. Used to maintain
 * the constant function prototype.
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit".
 */

int _myexit2(info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If there is an exit argument */
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
 * _mycd2 - Changes the current directory of the process.
 * @info: Pointer to a structure containing potential arguments. Used to maintain
 * the constant function prototype.
 * Return: Always 0
 */

int _mycd2(info_t *info)
{
   char *current_dir, *new_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_result = /* TODO: what should this be? */
				chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_result = chdir(new_dir);
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
		chdir_result = /* TODO: what should this be? */
			chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
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
 * _myhelp2 - Provides help information.
 * @info: Pointer to a structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp2(info_t *info)
{
	char **arguments;

	arguments = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arguments); /* temp att_unused workaround */
	return (0);
}


#include "shell.h"

/**
 * scaprg - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int scaprg(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = toi_err(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			err_rg(info, "Illegal number: ");
			_input(info->argv[1]);
			_charputs('\n');
			return (1);
		}
		info->err_num = toi_err(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * cmdrt_my - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int cmdrt_my(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		put_st("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = envst_get(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = envst_get(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_computed(info->argv[1], "-") == 0)
	{
		if (!envst_get(info, "OLDPWD="))
		{
			put_st(s);
			putrg_str('\n');
			return (1);
		}
		put_st(envst_get(info, "OLDPWD=")), putrg_str('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = envst_get(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		err_rg(info, "can't cd to ");
		_input(info->argv[1]), _charputs('\n');
	}
	else
	{
		liverg_set(info, "OLDPWD", envst_get(info, "PWD="));
		liverg_set(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * hand_st - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int hand_st(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	put_st("help call works. Function not yet implemented \n");
	if (0)
		put_st(*arg_array); /* temp att_unused workaround */
	return (0);
}

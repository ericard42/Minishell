#include "minishell.h"

int	cd_ext(char *path, char *tmp, int ret)
{
	path = find_var_env("HOME");
	tmp = ft_strjoin(tmp, getcwd(g_frame->pwd, PATH_MAX));
	ft_export(tmp);
	ret = chdir(path);
	free(path);
	free(tmp);
	if (ret == -1)
		ret = find_cd_env("HOME");
	return (ret);
}

int	cd_plus(int ret, char *oldpwd, char *tmp, char *path)
{
	if (ret == -1)
	{
		ft_errors(0, "No such file or directory");
		free(oldpwd);
		free(tmp);
		return (ret);
	}
	g_frame->ext_code = 0;
	if (ft_strcmp(path, "HOME") != 0)
		free(tmp);
	tmp = "OLDPWD=";
	tmp = ft_strjoin(tmp, oldpwd);
	ft_export(tmp);
	free(tmp);
	free(oldpwd);
	return (ret);
}

int	cd(char *path)
{
	int		ret;
	char	*tmp;
	char	*oldpwd;

	ret = 0;
	tmp = "PWD=";
	oldpwd = find_var_env("PWD");
	if (ft_strcmp(path, "HOME") == 0)
	{
		ret = cd_ext(path, tmp, ret);
		if (ret == -1)
		{
			free(oldpwd);
			ft_errors(0, "HOME not set");
			return (ret);
		}
	}
	else
	{
		ret = chdir(path);
		tmp = ft_strjoin(tmp, getcwd(g_frame->pwd, PATH_MAX));
		ft_export(tmp);
	}
	ret = cd_plus(ret, oldpwd, tmp, path);
	return (ret);
}

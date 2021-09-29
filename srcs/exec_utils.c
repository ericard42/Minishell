#include "minishell.h"

char	**separate_path_ext(char **path, char *tmp, int i, int nb)
{
	int	j;

	path = malloc(sizeof(char *) * (nb + 1));
	if (!path)
		ft_errors(1, "Malloc crashed");
	i = 0;
	nb = 0;
	while (tmp[i] != '\0')
	{
		j = 0;
		while (tmp[i] != ':' && tmp[i + 1] != '\0')
			i++;
		j = i;
		if (tmp[i] == ':' || tmp[i + 1] == '\0')
		{
			if (tmp[i + 1] == '\0')
				j++;
			path[nb] = malloc(sizeof(path) * (j + 1));
			if (!path[nb])
				ft_errors(1, "Malloc crashed");
			nb++;
		}
		i++;
	}
	return (path);
}

char	**separate_path_plus(int i, int nb, char **path, char *tmp)
{
	int	j;

	while (tmp[i] != '\0')
	{
		j = 0;
		while (tmp[i] != ':' && tmp[i + 1] != '\0')
			path[nb][j++] = tmp[i++];
		if (tmp[i] == ':' || tmp[i + 1] == '\0')
		{
			if (tmp[i + 1] == '\0')
			{
				path[nb][j] = tmp[i];
				j++;
			}
			path[nb][j] = '/';
			path[nb][j + 1] = '\0';
			nb++;
			i++;
		}
	}
	path[nb] = NULL;
	return (path);
}

char	**separate_path(void)
{
	char	**path;
	char	*tmp;
	int		i[2];

	tmp = find_var_env("PATH");
	if (tmp[0] == '\0')
	{
		path = malloc(sizeof(char *) * (1 + 1));
		if (!path)
			ft_errors(1, "Malloc crashed");
		path[0] = malloc(sizeof(char) * 1);
		path[0][0] = '\0';
		path[1] = NULL;
		free(tmp);
		return (path);
	}
	i[0] = 0;
	i[1] = 1;
	while (tmp[i[0]])
		if (tmp[i[0]++] == ':')
			i[1]++;
	path = separate_path_ext(NULL, tmp, i[0], i[1]);
	path = separate_path_plus(0, 0, path, tmp);
	free(tmp);
	return (path);
}

int	exec_loop_ext(int *i, char **arglist, char **env)
{
	struct stat	buf;

	if (stat(arglist[0], &buf) == 0 && buf.st_mode & S_IXUSR)
	{
		if (execve(arglist[0], arglist, env) == -1)
			i[1] = 1;
	}
	else if (stat(arglist[0], &buf) == 0)
		i[1] = 2;
	return (i[1]);
}

int	exec_loop(int *i, char **arglist, char **env, char **path)
{
	struct stat	buf;
	char		*str;

	if (i[0] == 0)
		i[1] = exec_loop_ext(i, arglist, env);
	else if (path[0][0] != '\0')
	{
		str = ft_strjoin(path[i[0]], arglist[0]);
		if (stat(str, &buf) == 0 && buf.st_mode & S_IXUSR)
		{
			if (execve(str, arglist, env) == -1)
				i[1] = 1 ;
		}
		else if (stat(str, &buf) == 0)
			i[1] = 2;
		free(str);
	}
	i[0]++;
	g_frame->i = i[0];
	return (i[1]);
}

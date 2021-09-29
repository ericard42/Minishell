#include "minishell.h"

char	**arglist_setup(t_list2 *cmd_lines)
{
	t_list2		*list;
	char		**arglist;
	int			i;

	i = 0;
	list = cmd_lines;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	list = cmd_lines;
	arglist = malloc(sizeof(*arglist) * (i + 1));
	if (!arglist)
		ft_errors(1, "Malloc crashed");
	i = 0;
	while (list != NULL)
	{
		arglist[i] = list->str;
		i++;
		list = list->next;
	}
	arglist[i] = NULL;
	return (arglist);
}

char	**env_setup(void)
{
	t_env		*en;
	char		**env;
	int			i;

	i = 0;
	en = g_frame->env;
	while (en != NULL)
	{
		en = en->next;
		i++;
	}
	en = g_frame->env;
	env = malloc(sizeof(*env) * (i + 1));
	if (!env)
		ft_errors(1, "Malloc crashed");
	i = 0;
	while (en != NULL)
	{
		env[i] = en->str;
		i++;
		en = en->next;
	}
	env[i] = NULL;
	return (env);
}

void	cmd_error(int x, char **arglist)
{
	if (x == 1 || x == 0)
	{
		ft_putstr_fd("\e[1;31m\e[1;4mNormishell\e[0m : ", 2);
		ft_putstr_fd(arglist[0], 2);
		ft_putchar_fd(':', 2);
		ft_putstr_fd(" command not found\n", 2);
		ft_exit(127);
	}
	else if (x == 2)
	{
		ft_putstr_fd("\e[1;31m\e[1;4mNormishell\e[0m : ", 2);
		ft_putstr_fd(arglist[0], 2);
		ft_putchar_fd(':', 2);
		ft_putstr_fd(" permission denied\n", 2);
		ft_exit(126);
	}
}

void	exec_ext(char **path, char **arglist, char **env, int *i)
{
	int	status;

	if (g_frame->exec_pid == 0)
	{
		while (path[i[0]] != NULL)
		{
			i[1] = exec_loop(i, arglist, env, path);
			i[0] = g_frame->i;
		}
		if (path[i[0]] == NULL)
		{
			cmd_error(i[1], arglist);
		}
	}
	free(env);
	i[0] = 0;
	waitpid(g_frame->exec_pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_frame->ext_code = WEXITSTATUS(status);
	}
	g_frame->exec_pid = 0;
}

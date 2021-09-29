#include "minishell.h"

int	exec(t_list2 *cmd_lines)
{
	char		**env;
	char		**arglist;
	char		**path;
	int			i[2];

	i[0] = 0;
	i[1] = 0;
	g_frame->sigquit = 1;
	arglist = arglist_setup(cmd_lines);
	env = env_setup();
	path = separate_path();
	g_frame->exec_pid = 0;
	g_frame->exec_pid = fork();
	exec_ext(path, arglist, env, i);
	while (path[i[0]] != NULL)
	{
		free(path[i[0]]);
		i[0]++;
	}
	free(arglist);
	free(path);
	return (0);
}

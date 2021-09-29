#include "minishell.h"

void	exit_3(void)
{
	t_input		*tmp_input;

	if (g_frame->input != NULL)
	{
		tmp_input = g_frame->input;
		while (tmp_input)
		{
			tmp_input = tmp_input->next;
			free(g_frame->input);
			g_frame->input = tmp_input;
		}
	}
}

void	exit_2(void)
{
	t_env		*tmp_env;
	t_history	*tmp_history;

	if (g_frame->env != NULL)
	{
		tmp_env = g_frame->env;
		while (tmp_env)
		{
			tmp_env = g_frame->env->next;
			free(g_frame->env->str);
			free(g_frame->env);
			g_frame->env = tmp_env;
		}
	}
	if (g_frame->history != NULL)
	{
		tmp_history = g_frame->history;
		while (tmp_history)
		{
			tmp_history = g_frame->history->next;
			free(g_frame->history->str);
			free(g_frame->history);
			g_frame->history = tmp_history;
		}
	}
}

void	ft_exit_ext(void)
{
	if (g_frame->path != NULL)
		free(g_frame->path);
	if (g_frame->cmd_line != NULL)
		free(g_frame->cmd_line);
	close(g_frame->cp_stdout);
	close(g_frame->cp_stdin);
	if (g_frame != NULL)
		free(g_frame);
}

void	ft_exit(int exit_code)
{
	exit_2();
	exit_3();
	if (g_frame->pipes != NULL)
		ft_lstdelete_pipe();
	if (g_frame->first_hist != NULL)
		free(g_frame->first_hist);
	if (g_frame->echo.text != NULL)
		free(g_frame->echo.text);
	if (g_frame->cmd_lines != NULL)
		ft_lstdeleteall_str(&g_frame->cmd_lines);
	if (g_frame->arg != NULL)
		ft_lstdeleteall_str(&g_frame->arg);
	if (g_frame->pwd != NULL)
		free(g_frame->pwd);
	if (g_frame->line != NULL)
		free(g_frame->line);
	ft_exit_ext();
	exit(exit_code);
}

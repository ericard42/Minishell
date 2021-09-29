#include "minishell.h"

void	ft_sigint(void)
{
	t_input	*tmp;

	tmp = g_frame->input;
	while (tmp)
	{
		tmp = tmp->next;
		free(g_frame->input);
		g_frame->input = tmp;
	}
	g_frame->ext_code = 130;
	ft_putstr_fd("^C\n", 1);
	ft_pwd(1);
	g_frame->cur_now = 0;
	g_frame->hist_now = NULL;
	g_frame->first_hist = NULL;
	g_frame->hist_pos = g_frame->hist_pos_last;
}

void	ft_sigquit(void)
{
	if (g_frame->sigquit == 0)
		return ;
	else
	{
		g_frame->ext_code = 131;
		g_frame->sigquit = 0;
		ft_putstr_fd("^\\Quit\n", 1);
		ft_pwd(1);
		g_frame->cur_now = 0;
		g_frame->hist_now = NULL;
		g_frame->first_hist = NULL;
		g_frame->hist_pos = g_frame->hist_pos_last;
	}
}

void	ft_signal(int code)
{
	if (g_frame->exec_pid != 0 || g_frame->pid != 0 || g_frame->first_pid != 0)
	{
		if (g_frame->pid == 0)
			ft_putchar_fd('\n', 1);
		g_frame->ext_code = 128 + code;
		return ;
	}
	if (code == SIGQUIT)
		ft_sigquit();
	if (code == SIGINT)
		ft_sigint();
}

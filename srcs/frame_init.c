#include "minishell.h"

void	frame_init_ext(void)
{
	g_frame->echo.text = NULL;
	g_frame->env = NULL;
	g_frame->fd = 1;
	g_frame->input = NULL;
	g_frame->hist_pos_last = 0;
	g_frame->p = 0;
	g_frame->cp_stdin = dup(STDIN_FILENO);
	g_frame->cp_stdout = dup(STDOUT_FILENO);
	g_frame->line = NULL;
	g_frame->first_hist = NULL;
	g_frame->ext_code = 0;
	g_frame->pid = NULL;
	g_frame->first_pid = 0;
	g_frame->exec_pid = 0;
}

void	frame_init(void)
{
	g_frame = (t_frame *)malloc(sizeof(t_frame));
	if (!g_frame)
		ft_errors(1, "Malloc crashed");
	g_frame->pipes = NULL;
	g_frame->operator = NULL;
	g_frame->redirector = 0;
	g_frame->arg = NULL;
	g_frame->last = 0;
	g_frame->history = NULL;
	g_frame->line_tmp = NULL;
	g_frame->cmd_line = NULL;
	g_frame->cmd_lines = NULL;
	g_frame->path = NULL;
	g_frame->ret = 0;
	g_frame->ret_str = NULL;
	g_frame->pwd = NULL;
	g_frame->echo.n = 0;
	frame_init_ext();
}

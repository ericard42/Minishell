#include "minishell.h"

void	pipe_child(t_operator *pipes, int *fd, int *save)
{
	free(g_frame->pid);
	if (pipes->prev)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (pipes->next)
	{
		close(save[0]);
		dup2(save[1], STDOUT_FILENO);
		close(save[1]);
	}
	if (g_frame->redirector == 0)
		cmd_redirector(pipes->cmd_lines);
	if (g_frame->redirector == 1)
	{
		if (special_operator(pipes->cmd_lines) == 0)
			cmd_redirector(pipes->cmd_lines);
	}
	close(fd[0]);
	close(fd[1]);
	close(save[0]);
	close(save[1]);
	ft_exit(g_frame->ext_code);
}

void	exit_pipe(int *fd, int *save)
{
	int	status;
	int	i;

	i = 0;
	while (i < g_frame->nb_pipes)
	{
		waitpid(g_frame->pid[i], &status, 0);
		i++;
	}
	g_frame->ext_code = WEXITSTATUS(status);
	close(fd[0]);
	close(fd[1]);
	close(save[0]);
	close(save[1]);
	dup2(g_frame->cp_stdin, STDIN_FILENO);
	dup2(g_frame->cp_stdout, STDOUT_FILENO);
	free(g_frame->pid);
	ft_exit(g_frame->ext_code);
}

void	run_pipe(void)
{
	t_operator	*pipes;
	int			fd[2][2];
	int			i;

	fd[0][0] = -1;
	fd[0][1] = -1;
	g_frame->pid = malloc(sizeof(pid_t) * g_frame->nb_pipes);
	if (!g_frame->pid)
		ft_errors(1, "Malloc crashed");
	pipes = g_frame->pipes;
	i = 0;
	while (pipes)
	{
		pipe(fd[1]);
		g_frame->pid[i] = 0;
		g_frame->pid[i] = fork();
		if (g_frame->pid[i] == 0)
			pipe_child(pipes, fd[0], fd[1]);
		close(fd[0][1]);
		close(fd[0][0]);
		ft_memmove(&fd[0], &fd[1], sizeof(int *));
		pipes = pipes->next;
		i++;
	}
	exit_pipe(fd[0], fd[1]);
}

void	run_first_fork(void)
{
	int		status;

	g_frame->first_pid = 0;
	g_frame->first_pid = fork();
	if (g_frame->first_pid == 0)
		run_pipe();
	waitpid(g_frame->first_pid, &status, 0);
	g_frame->ext_code = WEXITSTATUS(status);
	g_frame->first_pid = 0;
}

void	pipe_redirector(void)
{
	if (g_frame->p == 0 && g_frame->redirector == 0)
		cmd_redirector(g_frame->cmd_lines);
	if (g_frame->p == 0 && g_frame->redirector == 1)
		special_operator(g_frame->cmd_lines);
	if (g_frame->p == 1)
		run_first_fork();
}

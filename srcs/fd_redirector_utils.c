#include "minishell.h"

int	fd_redirector_1(t_operator *operator, int *fd)
{
	int		fd1;
	t_list2	*cmd_lines;

	fd1 = fd[0];
	cmd_lines = operator->cmd_lines->next;
	fd1 = open(cmd_lines->str, O_RDWR | O_CREAT | O_TRUNC, 0666);
	close(STDOUT_FILENO);
	dup2(fd1, STDOUT_FILENO);
	close(fd1);
	return (0);
}

int	fd_redirector_2(t_operator *operator, int *fd)
{
	int		fd1;
	t_list2	*cmd_lines;

	fd1 = fd[0];
	cmd_lines = operator->cmd_lines->next;
	fd1 = open(cmd_lines->str, O_RDWR | O_CREAT | O_APPEND, 0666);
	close(STDOUT_FILENO);
	dup2(fd1, STDOUT_FILENO);
	close(fd1);
	return (0);
}

void	fd_redirector_3_error(t_list2 *cmd_lines, int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	ft_putstr_fd("\e[1;31m\e[1;4mNormishell\e[0m : ", 2);
	ft_putstr_fd(cmd_lines->str, 2);
	ft_putstr_fd(": No such file  or directory\n", 2);
	g_frame->ext_code = 1;
	close(fd[0]);
	close(fd[1]);
}

int	fd_redirector_3(t_operator *operator, int *fd)
{
	int		fd2;
	t_list2	*cmd_lines;

	fd2 = fd[0];
	cmd_lines = operator->cmd_lines->next;
	fd2 = open(cmd_lines->str, O_RDWR);
	if (fd2 == -1)
	{
		fd_redirector_3_error(cmd_lines, fd);
		return (1);
	}
	close(STDIN_FILENO);
	dup2(fd2, STDIN_FILENO);
	close(fd2);
	return (0);
}

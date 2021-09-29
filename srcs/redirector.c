#include "minishell.h"

void	ft_lstdelete_operator(void)
{
	t_operator	*tmp;

	tmp = g_frame->operator;
	while (g_frame->operator != NULL)
	{
		ft_lstdeleteall_str(&g_frame->operator->cmd_lines);
		tmp = g_frame->operator->next;
		free(g_frame->operator);
		g_frame->operator = tmp;
	}
}

int	special_operator(t_list2 *cmd_lines)
{
	t_list2	*tmp;

	tmp = cmd_lines;
	while (tmp)
	{
		if (tmp->str[0] == '<' || tmp->str[0] == '>')
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (0);
	tmp = NULL;
	tmp = redirector_4(cmd_lines, tmp);
	ft_lstdeleteall_str(&tmp);
	operator_redirection();
	ft_lstdelete_operator();
	return (1);
}

int	filename(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && str[i + 1] != '\0')
		{
			ft_errors(0, "ambiguous redirect");
			return (1);
		}
		i++;
	}
	return (0);
}

int	operator_redirection_ext(t_operator *operator, int *fd)
{
	while (operator != NULL)
	{
		if (ft_strcmp(operator->cmd_lines->str, ">") == 0)
		{
			if (fd_redirector_1(operator, fd) == 1)
				return (1);
		}
		else if (ft_strcmp(operator->cmd_lines->str, ">>") == 0)
		{
			if (fd_redirector_2(operator, fd) == 1)
				return (1);
		}
		else if (ft_strcmp(operator->cmd_lines->str, "<") == 0)
		{
			if (fd_redirector_3(operator, fd) == 1)
				return (1);
		}
		operator = operator->next;
	}
	return (0);
}

void	operator_redirection(void)
{
	int			fd[2];
	t_operator	*operator;

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	operator = g_frame->operator;
	if (operator_redirection_ext(operator, fd) == 1)
		return ;
	if (g_frame->operator->cmd_lines->next->next != NULL)
		cmd_redirector(g_frame->operator->cmd_lines->next->next);
	g_frame->redirector = 0;
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

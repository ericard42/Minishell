#include "minishell.h"
void	redirector_pipe_leaks(t_list2 *cmd_lines,
		t_list2 *tmp1, t_operator *pipes, int g)
{
	tmp1 = cmd_lines;
	while (tmp1)
	{
		tmp1 = tmp1->next;
		g++;
	}
	if (g_frame->p != 0)
	{
		while (pipes != NULL)
		{
			if (pipes->cmd_lines == cmd_lines)
			{
				ft_lstdeletenode_str(&pipes->cmd_lines, pipes->cmd_lines->next);
				ft_lstdeletenode_str(&pipes->cmd_lines, pipes->cmd_lines);
			}
			pipes = pipes->next;
		}
	}
	if (g > 2 || g_frame->p == 0)
	{
		ft_lstdeletenode_str(&g_frame->cmd_lines, cmd_lines->next);
		ft_lstdeletenode_str(&g_frame->cmd_lines, cmd_lines);
	}
}

t_list2	*redirector_1(t_list2 *cmd_lines, t_list2 *tmp)
{
	t_list2		*buf;
	t_operator	*pipes;
	int			g;

	g = 0;
	buf = cmd_lines->next->next;
	pipes = g_frame->pipes;
	push_str(&tmp, cmd_lines->next->str);
	push_str(&tmp, cmd_lines->str);
	if (buf != NULL)
	{
		while (buf->str[0] != '>' && buf->str[0] != '<' && buf != NULL)
		{
			append_str(&tmp, buf->str);
			if (buf->next != NULL)
				buf = buf->next;
			else
				break ;
		}
	}
	append_operator(&g_frame->operator, tmp);
	redirector_pipe_leaks(cmd_lines, cmd_lines, pipes, g);
	cmd_lines = g_frame->cmd_lines;
	tmp = NULL;
	return (cmd_lines);
}

t_list2	*redirector_4(t_list2 *cmd_lines, t_list2 *tmp)
{
	while (cmd_lines != NULL)
	{
		if (ft_strcmp(">>", cmd_lines->str) == 0)
		{
			cmd_lines = redirector_1(cmd_lines, tmp);
			tmp = NULL;
		}
		else if (ft_strcmp("<", cmd_lines->str) == 0)
		{
			cmd_lines = redirector_1(cmd_lines, tmp);
			tmp = NULL;
		}
		else if (ft_strcmp(">", cmd_lines->str) == 0)
		{
			cmd_lines = redirector_1(cmd_lines, tmp);
			tmp = NULL;
		}
		else
			append_str(&tmp, cmd_lines->str);
		if (cmd_lines != NULL)
			cmd_lines = cmd_lines->next;
	}
	return (tmp);
}

#include "minishell.h"

void	ft_lstdelete_pipe(void)
{
	t_operator	*tmp;

	tmp = g_frame->pipes;
	while (g_frame->pipes != NULL)
	{
		if (g_frame->pipes->cmd_lines != NULL)
			ft_lstdeleteall_str(&g_frame->pipes->cmd_lines);
		tmp = g_frame->pipes->next;
		free(g_frame->pipes);
		g_frame->pipes = tmp;
	}
}

void	append_operator(t_operator **head_ref, t_list2 *new_data)
{
	t_operator	*new_node;
	t_operator	*last;

	new_node = (t_operator *)malloc(sizeof(t_operator));
	if (!new_node)
		ft_errors(1, "Malloc crashed");
	last = *head_ref;
	new_node->cmd_lines = new_data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return ;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
	return ;
}

void	ft_lstprint_operator(t_operator *pipes)
{
	int	i;

	i = 0;
	while (pipes != NULL)
	{
		ft_putnbr_fd(i, 1);
		ft_putchar_fd('>', 1);
		ft_lstprint_str(pipes->cmd_lines);
		ft_putchar_fd('\n', 1);
		pipes = pipes->next;
		i++;
	}
}

int	chained_pipe(void)
{
	t_list2	*cmd_lines;
	t_list2	*tmp;

	cmd_lines = g_frame->cmd_lines;
	g_frame->pipes = NULL;
	tmp = NULL;
	g_frame->nb_pipes = 0;
	while (cmd_lines != NULL)
	{
		if (cmd_lines->str[0] == '|')
		{
			append_operator(&g_frame->pipes, tmp);
			g_frame->nb_pipes++;
			tmp = NULL;
		}
		else
			append_str(&tmp, cmd_lines->str);
		cmd_lines = cmd_lines->next;
	}
	append_operator(&g_frame->pipes, tmp);
	g_frame->nb_pipes++;
	return (1);
}

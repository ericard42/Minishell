#include "minishell.h"

void	delet_redir_amb(t_list2 *cmd_lines)
{
	int		i;
	t_list2	*tmp;

	i = 0;
	while (cmd_lines != NULL && cmd_lines->str[i] != '|'
		&& cmd_lines->str[i] != ';')
	{
		if (cmd_lines->str[0] != '"' && cmd_lines->str[0] != '\'')
		{
			tmp = cmd_lines->prev;
			ft_lstdeletenode_str(&g_frame->cmd_lines, cmd_lines->next);
			ft_lstdeletenode_str(&g_frame->cmd_lines, cmd_lines);
			cmd_lines = tmp;
		}
		if (cmd_lines != NULL)
			cmd_lines = cmd_lines->next;
	}
}

void	amb_redir(t_list2 *cmd_lines)
{
	t_list2	*tmp;

	cmd_lines = cmd_lines->prev;
	tmp = cmd_lines->prev;
	ft_lstdeletenode_str(&g_frame->cmd_lines, cmd_lines->next);
	ft_lstdeletenode_str(&g_frame->cmd_lines, cmd_lines);
	cmd_lines = tmp;
	if (cmd_lines != NULL)
	{
		delet_redir_amb(cmd_lines->next);
	}
	else
		delet_redir_amb(g_frame->cmd_lines);
}

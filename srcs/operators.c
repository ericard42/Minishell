#include "minishell.h"

int	verification_prev_next(t_list2 *cmd_lines, int p)
{
	if (p == 1)
	{
		if (cmd_lines->prev == NULL
			|| (cmd_lines->next == NULL && cmd_lines->str[1] == '\0'))
			return (0);
		if (cmd_lines->prev->str[0] == '|')
			return (0);
	}
	if (p == 0)
	{
		if ((cmd_lines->prev == NULL
				&& cmd_lines->next == NULL && cmd_lines->str[1] == '\0')
			|| (cmd_lines->next == NULL && cmd_lines->str[1] == '\0')
			|| (cmd_lines->next == NULL && cmd_lines->str[0] == '>'
				&& cmd_lines->str[1] == '>' && cmd_lines->str[2] == '\0'))
			return (0);
		if (cmd_lines->prev == NULL)
			return (1);
	}
	if (cmd_lines->prev->str[0] == '<' || cmd_lines->prev->str[0] == '>')
		return (0);
	return (1);
}

int	pipe_split(t_list2 *cmd_lines, int i)
{
	char	*tmp;

	tmp = NULL;
	if (i != 0)
	{
		tmp = ft_strdup(cmd_lines->str + i);
		ft_bzero(cmd_lines->str + i, ft_strlen(cmd_lines->str + i));
	}
	else if (i == 0 && cmd_lines->str[1] != '\0')
	{
		if (verification_prev_next(cmd_lines, 1) == 0)
			return (0);
		tmp = ft_strdup(cmd_lines->str + 1);
		ft_bzero(cmd_lines->str + 1, ft_strlen(cmd_lines->str + 1));
	}
	else if (i == 0 && cmd_lines->str[1] == '\0')
	{
		i = 1;
		if (verification_prev_next(cmd_lines, 1) == 0)
			return (0);
		return (1);
	}
	insertAfter_str(cmd_lines, tmp);
	free(tmp);
	return (1);
}

int	redirector_split(t_list2 *cmd_lines, int i)
{
	char	*tmp;

	if (i == 0 && cmd_lines->str[1] != '\0')
	{
		i = 1;
		if (verification_prev_next(cmd_lines, 0) == 0)
			return (0);
		if (cmd_lines->str[0] == '>' && cmd_lines->str[1] == '>')
		{
			if (cmd_lines->str[2] == '\0')
				return (1);
			i++;
		}
	}
	else if (i == 0 && cmd_lines->str[1] == '\0')
	{
		if (verification_prev_next(cmd_lines, 0) == 0)
			return (0);
		return (1);
	}
	tmp = ft_strdup(cmd_lines->str + i);
	ft_bzero(cmd_lines->str + i, ft_strlen(cmd_lines->str + i));
	insertAfter_str(cmd_lines, tmp);
	free(tmp);
	return (1);
}

int	operators_verification(void)
{
	t_list2	*cmd_lines;

	cmd_lines = g_frame->cmd_lines;
	g_frame->p = 0;
	g_frame->redirector = 0;
	while (cmd_lines)
	{
		if (operator_check(cmd_lines, '\0', 0) == 0)
			return (0);
		cmd_lines = cmd_lines->next;
	}
	return (1);
}

void	quotes_verification(void)
{
	t_list2	*cmd_lines;
	char	*tmp;

	cmd_lines = g_frame->cmd_lines;
	while (cmd_lines)
	{
		tmp = ft_strdup(cmd_lines->str);
		ft_bzero(cmd_lines->str, ft_strlen(cmd_lines->str));
		quotes_check(cmd_lines, tmp, '\0');
		free(tmp);
		cmd_lines = cmd_lines->next;
	}
}

#include "minishell.h"

int	redirector_split_utils(t_list2 *cmd_lines, char *tmp)
{
	int	i;

	i = 1;
	if (verification_prev_next(cmd_lines, 0) == 0)
		return (0);
	if (cmd_lines->str[0] == '>' && cmd_lines->str[1] == '>')
	{
		if (cmd_lines->str[2] == '\0')
			return (1);
		i++;
	}
	tmp = ft_strdup(cmd_lines->str + i);
	ft_bzero(cmd_lines->str + i, ft_strlen(cmd_lines->str + i));
	return (2);
}

int	split_redirector(t_list2 *cmd_lines, char pr, int i)
{
	if (pr == 'p')
	{
		g_frame->p = 1;
		if (pipe_split(cmd_lines, i) == 0)
		{
			ft_errors(0, "syntax error near unexpected token `|'");
			g_frame->ext_code = 2;
			return (0);
		}
		return (1);
	}
	if (pr == 'r')
	{
		g_frame->redirector = 1;
		if (redirector_split(cmd_lines, i) == 0)
		{
			ft_errors(0, "syntax error near unexpected token `newline'");
			g_frame->ext_code = 2;
			return (0);
		}
		return (1);
	}
	return (1);
}

int	operator_check(t_list2 *cmd_lines, char quote, int	i)
{
	while (cmd_lines->str[i] != '\0')
	{
		if (cmd_lines->str[i] == '\'' || cmd_lines->str[i] == '\"')
			quote = cmd_lines->str[i++];
		while (quote != '\0' && cmd_lines->str[i] != quote)
			i++;
		if (cmd_lines->str[i] == quote)
			quote = '\0';
		if (cmd_lines->str[i] == '|')
		{
			if (split_redirector(cmd_lines, 'p', i) == 0)
				return (0);
			return (1);
		}
		if (cmd_lines->str[i] == '<' || cmd_lines->str[i] == '>')
		{
			if (split_redirector(cmd_lines, 'r', i) == 0)
				return (0);
			return (1);
		}
		i++;
	}
	return (1);
}

void	quotes_check(t_list2 *cmd_lines, char *tmp, char quote)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
			quote = tmp[i++];
		while (quote != '\0' && tmp[i] != quote && tmp[i] != '\0')
			cmd_lines->str[j++] = tmp[i++];
		if (tmp[i] == quote)
		{
			i++;
			quote = '\0';
		}
		if (tmp[i] != '\'' && tmp[i] != '\"' && tmp[i] != '\0')
			cmd_lines->str[j++] = tmp[i++];
	}
}

int	redirector_verif(t_list2 *cmd_lines)
{
	int		ret;

	while (cmd_lines != NULL)
	{
		ret = 0;
		if (cmd_lines->str[0] == '>' || cmd_lines->str[0] == '<')
		{
			cmd_lines = cmd_lines->next;
			if (cmd_lines->str[0] != '"' && cmd_lines->str[0] != '\'')
				ret = filename(cmd_lines->str);
			if (ret == 1)
			{
				amb_redir(cmd_lines);
				break ;
			}
		}
		if (cmd_lines != NULL)
			cmd_lines = cmd_lines->next;
	}
	return (0);
}

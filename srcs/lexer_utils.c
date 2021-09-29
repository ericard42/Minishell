#include "./minishell.h"

t_quote	single_quote(t_quote quote)
{
	if (quote.si_start == 1 )
	{
		quote.si_end = 1;
		quote.si_start = 0;
	}
	else if (quote.si_start == 0)
	{
		quote.si_start = 1;
		quote.si_end = 0;
	}
	return (quote);
}

t_quote	double_quote(t_quote quote)
{
	if (quote.do_start == 1)
	{
		quote.do_end = 1;
		quote.do_start = 0;
	}
	else if (quote.do_start == 0)
	{
		quote.do_start = 1;
		quote.do_end = 0;
	}
	return (quote);
}

void	cut_ext(int j, int size, char *str)
{
	while (j < size)
	{
		str[j] = g_frame->line[g_frame->last + j];
		j++;
	}
	str[j] = '\0';
	if (g_frame->line[g_frame->last + j] == ';')
		j++;
	str = space_clear(str);
	if (str != NULL)
		append_str(&g_frame->cmd_lines, str);
	free(str);
	g_frame->last += j;
}

int	lexer_1(int i)
{
	if (g_frame->semicolon)
	{
		if (g_frame->semicolon != 1)
			i = g_frame->semicolon;
		else
			g_frame->semicolon = 0;
	}
	if (g_frame->semicolon == 0)
		g_frame->last = 0;
	if (g_frame->cmd_line != NULL)
		free(g_frame->cmd_line);
	g_frame->cmd_line = NULL;
	if (g_frame->cmd_lines != NULL)
		ft_lstdeleteall_str(&g_frame->cmd_lines);
	g_frame->cmd_lines = NULL;
	return (i);
}

int	lexer_2(int i)
{
	while (g_frame->line[i] == ' ' && g_frame->line[i] != '\0')
		i++;
	if (g_frame->line[i] == '\0')
	{
		g_frame->semicolon = 0;
		return (-1);
	}
	while (ft_isprint(g_frame->line[i]) == 1 && g_frame->line[i] != '\0')
	{
		if (g_frame->line[i] != ' ' && g_frame->line[i] != '\''
			&& g_frame->line[i] != '\"' && g_frame->line[i] != '$'
			&& g_frame->line[i] != ';')
			i++;
		else
			break ;
	}
	g_frame->i = i;
	return (0);
}

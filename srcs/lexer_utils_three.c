#include "minishell.h"

int	lexer_6(int i, t_quote quote)
{
	if (quote.do_start == 1 || quote.si_start == 1)
	{
		ft_errors(0, "error quotes");
		return (0);
	}
	if (g_frame->line[i] == '\0')
		g_frame->semicolon = 0;
	if (operators_verification() != 1)
		return (0);
	redirector_verif(g_frame->cmd_lines);
	quotes_verification();
	return (1);
}

int	lexer_7(int i, int j, t_quote quote)
{
	j = 0;
	if (lexer_2(i) == -1)
	{
		i = g_frame->i;
		return (1);
	}
	i = g_frame->i;
	if (g_frame->line[i] == ';' && (quote.si_start != 1
			&& quote.do_start != 1))
	{
		if (lexer_3(i) == 1)
			return (-1);
		i = g_frame-> i;
		return (1);
	}
	g_frame->i = i;
	g_frame->j = j;
	return (0);
}

int	lexer_8(int i, int j, t_quote quote)
{
	int	ret;

	ret = lexer_7(i, j, quote);
	if (ret != 0)
	{
		if (ret == -1)
			return (0);
		i = g_frame->i;
		j = g_frame->j;
		return (-1);
	}
	i = g_frame->i;
	j = g_frame->j;
	quote = lexer_5(i, j, quote);
	i = g_frame->i;
	j = g_frame->j;
	g_frame->quote = quote;
	return (1);
}

int	lexer_9(int i, int j, t_quote quote, int ret)
{
	while (g_frame->line[i] != '\0')
	{
		ret = lexer_8(i, j, quote);
		if (ret == 0)
			return (0);
		else if (ret == -1)
		{
			i = g_frame->i;
			j = g_frame->i;
			break ;
		}
		quote = g_frame->quote;
		i = g_frame->i;
		j = g_frame->j;
		if (g_frame->line[i] == '\0')
		{
			cut(i);
			break ;
		}
		if (j == 0)
			i++;
	}
	if (lexer_6(i, quote) == 0)
		return (0);
	return (1);
}

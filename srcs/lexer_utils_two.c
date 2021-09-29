#include "minishell.h"

t_quote	lexer_do(int i, int j, t_quote quote)
{
	quote = double_quote(quote);
	if (quote.do_end != 1 && j == 1)
		j = 0;
	if (quote.do_end == 1 && (g_frame->line[i + 1] != ' '
			&& g_frame->line[i + 1] != '\0'))
	{
		i++;
		j = 1;
	}
	else if (quote.do_end == 1)
	{
		cut(i + 1);
		i++;
	}
	g_frame->i = i;
	g_frame->j = j;
	return (quote);
}

t_quote	lexer_si(int i, int j, t_quote quote)
{
	quote = single_quote(quote);
	if (quote.si_end == 1 && (g_frame->line[i + 1] != ' '
			&& g_frame->line[i + 1] != '\0'))
	{
		i++;
		j = 1;
	}
	else if (quote.si_end == 1)
	{
		cut(i + 1);
		i++;
	}
	g_frame->i = i;
	g_frame->j = j;
	return (quote);
}

int	lexer_3(int i)
{
	if (g_frame->cmd_lines == NULL && g_frame->line[i - 1] == ' ')
	{
		ft_errors(0, "syntax error near unexpected token `;'");
		g_frame->semicolon = 0;
		return (1);
	}
	g_frame->semicolon = i + 1;
	if (g_frame->line[i - 1] != ' ')
		cut(i);
	g_frame->last = i + 1;
	g_frame->i = i;
	return (0);
}

int	lexer_4(int i, int j, t_quote quote)
{
	i += expension_new(i);
	j = 1;
	if (g_frame->line[i] == ' ' && quote.do_start != 1)
		cut(i);
	g_frame->j = j;
	return (i);
}

t_quote	lexer_5(int i, int j, t_quote quote)
{
	if (g_frame->line[i] == ' ' && (quote.si_start != 1
			&& quote.do_start != 1))
		cut(i);
	if (g_frame->line[i] == '\'' && quote.do_start != 1)
	{
		quote = lexer_si(i, j, quote);
		i = g_frame->i;
		j = g_frame->j;
	}
	if (g_frame->line[i] == '\"' && quote.si_start != 1)
	{
		quote = lexer_do(i, j, quote);
		i = g_frame->i;
		j = g_frame->j;
	}
	if (g_frame->line[i] == '$' && quote.si_start != 1)
	{
		i = lexer_4(i, j, quote);
		j = g_frame->j;
	}
	g_frame->i = i;
	g_frame->j = j;
	return (quote);
}

#include "minishell.h"

void	cut(int i)
{
	char	*str;
	int		size;
	int		j;

	j = 0;
	if (i == g_frame->last)
		return ;
	size = i - g_frame->last;
	if (size <= 0)
		return ;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		ft_errors(1, "Malloc crashed");
	cut_ext(j, size, str);
}

t_quote	init_quote(void)
{
	t_quote	quote;

	quote.do_start = 0;
	quote.do_end = 0;
	quote.si_start = 0;
	quote.si_end = 0;
	return (quote);
}

int	lexer_new(void)
{
	int		i;
	t_quote	quote;
	int		j;
	int		ret;

	j = 0;
	ret = 0;
	quote = init_quote();
	i = lexer_1(0);
	if (g_frame->line[0] == '\0')
		return (1);
	if (lexer_9(i, j, quote, ret) == 0)
		return (0);
	return (1);
}

void	stock_input(void)
{
	while (42)
	{
		g_frame->semicolon = 1;
		g_frame->sigquit = 0;
		ft_pwd(1);
		input_loop();
		input_join();
		add_history();
		ft_putchar_fd('\n', 1);
		while (g_frame->semicolon != 0)
		{
			if (lexer_new() == 0)
				break ;
			if (g_frame->p == 1)
				chained_pipe();
			restore_term();
			if (g_frame->cmd_lines != NULL)
				pipe_redirector();
			init_term();
			ft_lstdelete_pipe();
		}
	}
}

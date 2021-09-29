#include "minishell.h"

void	echo_ext(t_list2 *cmd_lines)
{
	char	*str;

	if (cmd_lines->str[0] != '-' || full_n(cmd_lines->str) == 1)
	{
		str = ft_strdup(cmd_lines->str);
		cmd_lines = cmd_lines->next;
		while (cmd_lines != NULL && ft_strcmp("|", cmd_lines->str) != 0)
		{
			str = ft_strjoin_space(str, cmd_lines->str);
			cmd_lines = cmd_lines->next;
		}
		g_frame->echo.text = ft_strdup(str);
		free(str);
	}
	else
		g_frame->echo.text = ft_strdup("");
	ft_echo();
}

void	echo_call(t_list2 *cmd_lines)
{
	g_frame->echo.n = 0;
	if (cmd_lines == NULL)
	{
		ft_putchar_fd('\n', 1);
		g_frame->ext_code = 0;
		return ;
	}
	if (cmd_lines->str[0] == '-' && cmd_lines->str[1] == 'n')
	{
		if (full_n(cmd_lines->str) == 0)
		{
			g_frame->echo.n = 1;
			while (cmd_lines->next != NULL)
			{
				if (full_n(cmd_lines->str) == 0)
					cmd_lines = cmd_lines->next;
				else
					break ;
			}
		}
	}
	echo_ext(cmd_lines);
}

void	ft_echo(void)
{
	ft_putstr_fd(g_frame->echo.text, g_frame->fd);
	if (g_frame->echo.text)
		free(g_frame->echo.text);
	g_frame->echo.text = NULL;
	if (g_frame->echo.n == 0)
		ft_putchar_fd('\n', g_frame->fd);
	g_frame->echo.n = 0;
	g_frame->ext_code = 0;
}

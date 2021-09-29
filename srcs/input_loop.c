#include "minishell.h"

void	first_hist(void)
{
	t_input	*tmp;
	int		i;

	i = 0;
	tmp = g_frame->input;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	g_frame->first_hist = malloc(sizeof(char) * (i + 1));
	if (!g_frame->first_hist)
		ft_errors(1, "Malloc crashed");
	tmp = g_frame->input;
	i = 0;
	while (tmp)
	{
		g_frame->first_hist[i] = tmp->c;
		i++;
		tmp = tmp->next;
	}
	g_frame->first_hist[i] = '\0';
}

void	change_input(void)
{
	int		first;
	int		i;

	first = 0;
	if (g_frame->first_hist == NULL)
		first_hist();
	while (g_frame->cur_now != 0)
		del_char_input();
	g_frame->input = NULL;
	i = 0;
	while (g_frame->hist_now[i] != '\0')
	{
		add_char_input(g_frame->hist_now[i]);
		i++;
	}
	g_frame->hist_now = NULL;
}

void	read_char(void)
{
	char	buffer[5];

	while (42)
	{
		read(STDIN_FILENO, buffer, 4);
		if (buffer[0] >= 32 && buffer[0] <= 126)
			add_char_input(buffer[0]);
		else if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 'A')
			history_up();
		else if (buffer[0] == 27 && buffer[1] == '[' && buffer[2] == 'B')
			history_down();
		else if (buffer[0] == 4)
		{
			if (g_frame->input == NULL)
			{
				ft_putstr_fd("exit\n", 1);
				normishell_goodbye();
				ft_exit(g_frame->ext_code);
			}
		}
		else if (buffer[0] == DEL_KEY)
			del_char_input();
		else if (buffer[0] == ENTER_KEY)
			break ;
	}
}

void	input_loop(void)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	if (g_frame->line != NULL)
		free(g_frame->line);
	g_frame->line = NULL;
	g_frame->cur_now = 0;
	g_frame->hist_now = NULL;
	if (g_frame->first_hist != NULL)
		free(g_frame->first_hist);
	g_frame->first_hist = NULL;
	g_frame->hist_pos = g_frame->hist_pos_last;
	read_char();
}

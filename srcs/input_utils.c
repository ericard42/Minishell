#include "minishell.h"

void	input_join_count(void)
{
	int		i;
	t_input	*tmp;

	i = 0;
	tmp = g_frame->input;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	g_frame->line = malloc(sizeof(char) * (i + 1));
	if (!g_frame->line)
		ft_errors(1, "Malloc crashed");
}

void	input_join(void)
{
	t_input	*tmp;
	int		i;

	if (g_frame->line)
		free(g_frame->line);
	g_frame->line = NULL;
	input_join_count();
	tmp = g_frame->input;
	i = 0;
	if (g_frame->input != NULL)
	{
		tmp = g_frame->input;
		while (tmp)
		{
			g_frame->line[i] = tmp->c;
			i++;
			tmp = g_frame->input->next;
			free(g_frame->input);
			g_frame->input = tmp;
		}
	}
	g_frame->line[i] = '\0';
	g_frame->input = NULL;
}

void	add_char_input(char c)
{
	t_input	*new;
	t_input	*tmp;

	new = malloc(sizeof(t_input));
	if (!new)
		ft_errors(1, "Malloc crashed");
	tmp = g_frame->input;
	new->c = c;
	new->next = NULL;
	if (g_frame->input == NULL)
	{
		new->prev = NULL;
		g_frame->input = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	g_frame->cur_now++;
	ft_putchar_fd(c, 0);
}

int	del_char_input(void)
{
	t_input	*tmp;

	if (g_frame->cur_now == 0)
		return (0);
	if (g_frame->input == NULL)
		return (0);
	tmp = g_frame->input;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->prev == NULL)
	{
		free(g_frame->input);
		g_frame->input = NULL;
	}
	else
	{
		tmp->prev->next = tmp->next;
		free(tmp);
	}
	tputs(tgetstr("le", NULL), 0, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	g_frame->cur_now--;
	return (1);
}

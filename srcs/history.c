#include "minishell.h"

void	add_history_next(t_history *new)
{
	t_history	*tmp;

	if (g_frame->history == NULL)
	{
		new->prev = NULL;
		g_frame->history = new;
	}
	else
	{
		tmp = g_frame->history;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (ft_strcmp(g_frame->line, tmp->str) == 0)
		{
			free(new->str);
			free(new);
			return ;
		}
		new->prev = tmp;
		tmp->next = new;
	}
	g_frame->hist_pos_last++;
}

int	add_history(void)
{
	t_history	*new;

	if (g_frame->line[0] == '\0')
		return (0);
	new = malloc(sizeof(t_history));
	if (!new)
		ft_errors(1, "Malloc crashed");
	new->str = ft_strdup(g_frame->line);
	new->pos = g_frame->hist_pos_last;
	new->next = NULL;
	add_history_next(new);
	return (1);
}

int	history_up(void)
{
	t_history	*tmp;

	tmp = g_frame->history;
	if (tmp == NULL || tmp->pos == g_frame->hist_pos)
		return (0);
	while (tmp->pos != g_frame->hist_pos - 1)
		tmp = tmp->next;
	g_frame->hist_pos--;
	g_frame->hist_now = tmp->str;
	change_input();
	return (1);
}

int	history_down(void)
{
	t_history	*tmp;

	tmp = g_frame->history;
	if (tmp == NULL || g_frame->hist_pos_last == g_frame->hist_pos)
		return (0);
	if (g_frame->hist_pos_last - 1 != g_frame->hist_pos)
		while (tmp->pos != g_frame->hist_pos + 1)
			tmp = tmp->next;
	if (g_frame->hist_pos_last - 1 == g_frame->hist_pos)
	{
		g_frame->hist_now = g_frame->first_hist;
		change_input();
		free(g_frame->first_hist);
		g_frame->first_hist = NULL;
	}
	else
	{
		g_frame->hist_now = tmp->str;
		change_input();
	}
	g_frame->hist_pos++;
	return (1);
}

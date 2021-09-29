#include "minishell.h"

char	*find_var_env(char *var)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (var[i] == '?')
	{
		return (ft_itoa(g_frame->ext_code));
	}
	tmp = g_frame->env;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->str[i] == var[i])
		{
			if (tmp->str[i + 1] == '=' && var[i + 1] == '\0')
			{
				if (tmp->str[i + 2] == '\0')
					return (ft_calloc(1, 1));
				return (ft_strdup(tmp->str + (i + 2)));
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (ft_calloc(1, 1));
}

int	find_cd_env(char *var)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = g_frame->env;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->str[i] == var[i])
		{
			if (tmp->str[i + 1] == '=' && var[i + 1] == '\0')
				return (0);
			i++;
		}
		tmp = tmp->next;
	}
	return (-1);
}

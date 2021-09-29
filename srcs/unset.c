#include "minishell.h"

void	free_node_env(t_env *tmp)
{
	t_env	*tmpprev;
	int		i;

	i = 0;
	tmpprev = g_frame->env;
	if (tmpprev->str == tmp->str)
	{
		g_frame->env = g_frame->env->next;
		i = 1;
	}
	while (tmpprev->next->str != tmp->str)
		tmpprev = tmpprev->next;
	if (i == 0)
		tmpprev->next = tmpprev->next->next;
	if (tmp->str != NULL)
		free(tmp->str);
	free(tmp);
}

void	unset_call(t_list2 *cmd_lines)
{
	int	x;

	x = 0;
	while (cmd_lines)
	{
		if (cmd_lines->str[0] == '\0')
		{
			ft_err_identifier(cmd_lines->str);
			x = g_frame->ext_code;
		}
		else
			g_frame->ext_code = ft_unset(cmd_lines->str);
		cmd_lines = cmd_lines->next;
	}
	if (x != 0)
		g_frame->ext_code = x;
}

int	unset_error(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && !ft_isalnum(var[i]) && var[i] != '_')
		{
			ft_err_identifier(var);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char *var)
{
	t_env		*tmp;
	int			i;

	tmp = g_frame->env;
	if (var == NULL)
		return (1);
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->str[i] == var[i])
		{
			if (tmp->str[i + 1] == '=' && var[i + 1] == '\0')
			{
				free_node_env(tmp);
				return (0);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (unset_error(var));
}

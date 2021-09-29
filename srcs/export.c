#include "minishell.h"
void	export_call(t_list2 *cmd_lines)
{	
	int	x;

	x = 0;
	if (cmd_lines == NULL)
	{
		print_env_declare();
		return ;
	}
	while (cmd_lines != NULL)
	{
		if (cmd_lines->str[0] == '\0')
		{
			ft_err_identifier(cmd_lines->str);
			x = g_frame->ext_code;
		}
		else
			g_frame->ext_code = ft_export(cmd_lines->str);
		cmd_lines = cmd_lines->next;
	}
	if (x != 0)
		g_frame->ext_code = x;
}

int	ft_export_ext(char *str, int i)
{
	t_env	*new;
	t_env	*tmp;

	if (str[i] == '\0')
		return (0);
	if (verif_env(str) == 1)
		return (0);
	new = malloc(sizeof(t_env));
	if (!new)
		ft_errors(1, "Malloc crashed");
	new->str = ft_strdup(str);
	new->next = NULL;
	if (!g_frame->env)
		g_frame->env = new;
	else
	{
		tmp = g_frame->env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int	ft_export(char *str)
{
	int		i;

	if (str == NULL)
		return (1);
	i = 0;
	if (str[0] == '=')
	{
		ft_err_identifier(str);
		return (1);
	}
	while (str[i] != '=' && str[i] != '\0')
	{
		if (!ft_isalpha(str[i]) && !ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_err_identifier(str);
			return (1);
		}
		i++;
	}
	return (ft_export_ext(str, i));
}

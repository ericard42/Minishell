#include "minishell.h"

void	print_env(void)
{
	t_env	*env;

	env = g_frame->env;
	while (env != NULL)
	{
		ft_putstr_fd(env->str, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

void	print_env_declare(void)
{
	t_env	*env;

	env = g_frame->env;
	while (env != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->str, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

int	verif_env(char *str)
{
	t_env	*tmp;
	int		i;

	tmp = g_frame->env;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->str[i] == str[i])
		{
			if (tmp->str[i + 1] == '=' && str[i + 1] == '=')
			{
				free(tmp->str);
				tmp->str = ft_strdup(str);
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	env_init_plus(t_env *env, char **env_str, int i)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		ft_errors(1, "Malloc crashed");
	new->str = ft_strdup(env_str[i]);
	new->next = NULL;
	env->next = new;
}

void	env_init(char **env_str)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		exit(0);
	if (!env_str)
	{
		env->str = ft_strdup("");
		env->next = NULL;
		g_frame->env = env;
		return ;
	}
	env->str = ft_strdup(env_str[0]);
	env->next = NULL;
	g_frame->env = env;
	i = 1;
	while (env_str[i])
	{
		env_init_plus(env, env_str, i);
		env = env->next;
		i++;
	}
}

#include "minishell.h"

int	exit_call(t_list2 *str)
{
	if (str == NULL)
	{
		if (g_frame->p == 0)
			normishell_goodbye();
		ft_exit(g_frame->ext_code);
	}
	else if (ft_isdigit_str(str->str) == 0)
	{
		ft_putstr_fd("\e[1;31m\e[1;4mNormishell\e[0m : ", 2);
		ft_putstr_fd("numeric argument required\n", 2);
		if (g_frame->p == 0)
			normishell_goodbye();
		ft_exit(2);
	}
	else if (str->next != NULL)
		ft_errors(0, "too many arguments");
	else
	{
		if (g_frame->p == 0)
			normishell_goodbye();
		ft_exit(ft_atoi(str->str));
	}
	return (1);
}

int	cmd_redirector_ext(t_list2 *cmd_lines, char *word, t_list2 *tmp)
{
	if (ft_strcmp(word, "pwd") == 0)
		ft_pwd(0);
	else if (ft_strcmp(word, "export") == 0)
		export_call(tmp);
	else if (ft_strcmp(word, "echo") == 0)
		echo_call(tmp);
	else if (ft_strcmp(word, "unset") == 0)
		unset_call(tmp);
	else if (ft_strcmp(word, "env") == 0)
		print_env();
	else if (ft_strcmp(word, "exit") == 0)
		g_frame->ext_code = exit_call(tmp);
	else
		exec(cmd_lines);
	return (0);
}

int	cmd_redirector(t_list2 *cmd_lines)
{
	int		i;
	t_list2	*tmp;
	char	*word;

	tmp = cmd_lines;
	word = tmp->str;
	tmp = tmp->next;
	i = 0;
	if (ft_strcmp(word, "cd") == 0)
	{
		if (tmp != NULL && tmp->next != NULL)
			ft_errors(0, "cd: too many arguments");
		else if (tmp == NULL)
			cd("HOME");
		else
			cd(tmp->str);
	}
	else
		cmd_redirector_ext(cmd_lines, word, tmp);
	return (1);
}

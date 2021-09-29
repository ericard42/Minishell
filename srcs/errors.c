#include "minishell.h"

void	ft_errors(int exit, char *error)
{
	ft_putstr_fd("\e[1;31m\e[1;4mNormishell\e[0m : ", 2);
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
	g_frame->ext_code = 1;
	if (exit == 1)
		ft_exit(1);
}

void	ft_err_identifier(char *str)
{
	ft_putstr_fd("\e[1;31m\e[1;4mNormishell\e[0m : ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_frame->ext_code = 1;
}

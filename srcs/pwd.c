#include "minishell.h"

void	ft_pwd(int deb)
{
	g_frame->pwd = getcwd(g_frame->pwd, PATH_MAX);
	if (deb == 0)
	{
		ft_putstr_fd(g_frame->pwd, 1);
		ft_putchar_fd('\n', 1);
		g_frame->ext_code = 0;
	}
	if (deb == 1)
	{
		ft_putstr_fd("\e[1;34m", 1);
		ft_putstr_fd(g_frame->pwd, 1);
		ft_putstr_fd("\e[1;35m ", 1);
		ft_putstr_fd(" -> ", 1);
		ft_putstr_fd("\e[0m ", 1);
	}
}

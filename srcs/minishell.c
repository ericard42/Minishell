#include "minishell.h"

static void	normishell_welcome(void)
{
	ft_putstr_fd("\e[1;36m\e[1;1m", 1);
	ft_putstr_fd("WELCOME ON ", 1);
	ft_putstr_fd("\e[1;35m\e[1;4m", 1);
	ft_putstr_fd("NORMISHELL", 1);
	ft_putstr_fd("\e[0m\e[1;36m", 1);
	ft_putstr_fd(" ! ", 1);
	ft_putstr_fd("Miaou...\n\n", 1);
	ft_putstr_fd("\e[0m", 1);
}

void	normishell_goodbye(void)
{
	ft_putstr_fd("\e[1;36m\e[1;1m", 1);
	ft_putstr_fd("SEE YOU SOON ON ", 1);
	ft_putstr_fd("\e[1;35m\e[1;4m", 1);
	ft_putstr_fd("NORMISHELL", 1);
	ft_putstr_fd("\e[0m\e[1;36m", 1);
	ft_putstr_fd(" ! ", 1);
	ft_putstr_fd("Miaou... AND DON'T FORGET THE CATNIP NEXT TIME !\n\n", 1);
	ft_putstr_fd("\e[0m", 1);
}

static void	shell_count(void)
{
	char	*tmp;
	int		ret;
	char	*sh;

	sh = "SHLVL=";
	tmp = find_var_env("SHLVL");
	ret = ft_atoi(tmp);
	free(tmp);
	ret += 1;
	tmp = ft_itoa(ret);
	sh = ft_strjoin(sh, tmp);
	ft_export(sh);
	free(sh);
	free(tmp);
}

int	main(int argc, char **argv, char **env)
{
	char	*pwd;

	g_frame = NULL;
	argc = 0;
	argv = NULL;
	frame_init();
	if (*env != NULL)
		env_init(env);
	if (*env == NULL)
	{
		ft_export("TERM=xterm-256color");
		pwd = ft_strjoin("PWD=", getcwd(g_frame->pwd, PATH_MAX));
		ft_export(pwd);
		free(pwd);
	}
	termcaps_init();
	shell_count();
	normishell_welcome();
	stock_input();
}

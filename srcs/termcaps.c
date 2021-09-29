#include "minishell.h"

int	termcaps_init(void)
{
	int				ret;
	char			*term_type;

	init_term();
	term_type = find_var_env("TERM");
	ret = tgetent(NULL, term_type);
	free(term_type);
	if (ret != 1)
		return (-1);
	return (0);
}

void	init_term(void)
{
	struct termios	infos;

	if (tcgetattr(0, &g_frame->origin_term) == -1)
		ft_exit(8);
	ft_memcpy(&infos, &g_frame->origin_term, sizeof(struct termios));
	infos.c_lflag &= ~ECHO;
	infos.c_lflag &= ~ICANON;
	if (tcsetattr(0, TCSANOW, &infos) == -1)
		ft_exit(9);
}

void	restore_term(void)
{
	if (tcsetattr(0, TCSANOW, &g_frame->origin_term) == -1)
		ft_exit(7);
}

#include "minishell.h"

void	exit_code(void)
{
	char	*tmp;
	char	*ext;
	char	*ret;

	tmp = ft_strdup("?=");
	ext = ft_itoa(g_frame->ext_code);
	ret = ft_strjoin(tmp, ext);
	ft_export(tmp);
	free(tmp);
	free(ext);
	free(ret);
}

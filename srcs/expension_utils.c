#include "minishell.h"

int	expension_ext_ext(int i, int y, int n, int ret)
{
	char	*tmp;
	char	*str;

	str = malloc(sizeof(char) * y + 1);
	tmp = expension_ext(i - y, str, n);
	free(str);
	ret = ft_strlen(tmp);
	g_frame->line = ft_strjoin_n(g_frame->line, tmp, 0, n);
	return (ret);
}

char	*expension_plus(char *tmp, int x, int y, int n)
{
	int	j;

	j = n;
	if (g_frame->cmd_lines != NULL)
	{
		if (ft_strcmp(g_frame->cmd_lines->str, "echo") == 0
			&& tmp != NULL && tmp[0] != '\0')
		{
			while (n != 0)
			{
				if (g_frame->line[n] == '"')
					y++;
				if (g_frame->line[n] == '>' || g_frame->line[n] == '<')
					x = 1;
				n--;
			}
			if (g_frame->line[j - 1] == ' ')
				tmp = space_clear(tmp);
			if (x != 1 && y == 0)
				tmp = expension_quoting(tmp);
			else if (!y / 2)
				tmp = expension_quoting(tmp);
		}
	}
	return (tmp);
}

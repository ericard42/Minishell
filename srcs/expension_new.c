#include "minishell.h"

char	*ft_strjoin_n_ext(char *s1, char *strjoin, char *s2, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && i != n)
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (s2[j])
		strjoin[i++] = s2[j++];
	j = i - j + 1;
	while ((ft_isalpha(s1[j]) == 1 || ft_isalnum(s1[j]) == 1 || s1[j] == '?'
			|| s1[j] == '_') && s1[j] != '\0')
		j++;
	while (s1[j])
	{
		strjoin[i] = s1[j];
		i++;
		j++;
	}
	strjoin[i] = '\0';
	return (strjoin);
}

char	*ft_strjoin_n(char *s1, char *s2, int y, int n)
{
	int		i;
	int		j;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) - y;
	j = ft_strlen(s2);
	strjoin = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!strjoin)
		ft_errors(1, "Malloc crashed");
	if (strjoin == NULL)
		return (strjoin);
	strjoin = ft_strjoin_n_ext(s1, strjoin, s2, n);
	free(s1);
	free(s2);
	return (strjoin);
}

char	*expension_quoting(char *str)
{
	int		i;
	int		len;
	char	*tmp;
	t_list2	*cmd_lines;

	i = 0;
	cmd_lines = g_frame->cmd_lines;
	while (cmd_lines->next != NULL)
		cmd_lines = cmd_lines->next;
	if (cmd_lines->str[0] == '>' || cmd_lines->str[0] == '<')
		return (str);
	len = ft_strlen(str);
	tmp = malloc(sizeof(char) * len + 3);
	tmp[0] = '"';
	while (str[i] != '\0')
	{
		tmp[i + 1] = str[i];
		i++;
	}
	tmp[i + 1] = '"';
	tmp[i + 2] = '\0';
	free(str);
	return (tmp);
}

char	*expension_ext(int i, char *str, int n)
{
	int		y;
	int		x;
	char	*tmp;

	y = 0;
	x = 0;
	while ((ft_isalpha(g_frame->line[i]) == 1
			|| ft_isalnum(g_frame->line[i]) == 1 || g_frame->line[i] == '?'
			|| g_frame->line[i] == '_') && g_frame->line[i] != '\0')
	{
		str[y] = g_frame->line[i];
		y++;
		i++;
	}
	str[y] = '\0';
	tmp = find_var_env(str);
	y = 0;
	tmp = expension_plus(tmp, x, y, n);
	return (tmp);
}

int	expension_new(int i)
{
	int		y;
	int		ret;
	int		n;

	y = 0;
	n = i;
	ret = 0;
	i++;
	if (g_frame->line[i] == ' ' || g_frame->line[i] == '\0'
		|| g_frame->line[i] == '"')
		return (i);
	while ((ft_isalpha(g_frame->line[i]) == 1
			|| ft_isalnum(g_frame->line[i]) == 1 || g_frame->line[i] == '?'
			|| g_frame->line[i] == '_') && g_frame->line[i] != '\0')
	{
		y++;
		i++;
	}
	if (y == 0 && g_frame->line[i - y] != '\"' && g_frame->line[i - y] != '\'')
		return (1);
	ret = expension_ext_ext(i, y, n, ret);
	return (ret);
}

#include "minishell.h"

static char	*ft_strjoin_space_ext(char *strjoin, int i, int j, char const *s2)
{
	strjoin[i] = ' ';
	i++;
	while (s2[j])
	{
		strjoin[i + j] = s2[j];
		j++;
	}
	strjoin[i + j] = '\0';
	return (strjoin);
}

char	*ft_strjoin_space(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	strjoin = (char *)malloc(sizeof(char) * (i + j + 2));
	if (strjoin == NULL)
		ft_errors(1, "Malloc crashed");
	i = 0;
	j = 0;
	while (s1[i])
	{
		strjoin[i] = s1[i];
		i++;
	}
	if (s1 != NULL)
		free(s1);
	strjoin = ft_strjoin_space_ext(strjoin, i, j, s2);
	return (strjoin);
}

int	full_n(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (1);
	if (str[i] == '-')
		i++;
	while (str[i] == 'n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (1);
}

#include "minishell.h"

char	*space_clear_ext(char *str, int i, int n, int d)
{
	char	*string;

	while (str[i] != '\0')
		i++;
	while (str[i - 1] == ' ')
		i--;
	n = i;
	i = d;
	string = ft_calloc(n - d + 1, sizeof(char));
	if (!string)
		ft_errors(1, "Malloc crashed");
	d = 0;
	while (str[i] != '\0' && i < n)
	{
		string[d] = str[i];
		i++;
		d++;
	}
	string[d] = '\0';
	free(str);
	return (string);
}

char	*space_clear(char *str)
{
	int			i;
	int			j;
	int			n;
	int			d;
	char		*string;

	i = 0;
	j = 0;
	n = 0;
	d = 0;
	string = NULL;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	d = i;
	string = space_clear_ext(str, i, n, d);
	return (string);
}

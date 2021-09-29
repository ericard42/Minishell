/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addubois <addubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 14:04:30 by addubois          #+#    #+#             */
/*   Updated: 2021/07/05 22:48:25 by addubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line(char **s, char **line)
{
	int		len;
	char	*aux;

	len = 0;
	while (((*s)[len] != '\n' && (*s)[len] != '\0'))
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_substr_gnl(*s, 0, len);
		aux = ft_strdup_gnl(&((*s)[len + 1]));
		free(*s);
		*s = aux;
	}
	else
	{
		*line = ft_strdup_gnl(*s);
		free(*s);
		*s = NULL;
		return (0);
	}
	return (1);
}

int	return_value(int fd, int n_bytes, char **s, char **line)
{
	if (n_bytes < 0)
		return (-1);
	else if (n_bytes == 0 && s[fd] == NULL)
	{
		*line = ft_strdup_gnl("");
		return (0);
	}
	else
		return (new_line(&s[fd], line));
}

int	get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	int				n_bytes;
	static char		*s[FD_SIZE];
	char			*aux;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	while (n_bytes > 0)
	{
		n_bytes = read(fd, buff, BUFFER_SIZE);
		buff[n_bytes] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup_gnl(buff);
		else
		{
			aux = ft_strjoin_gnl(s[fd], buff);
			free(s[fd]);
			s[fd] = aux;
		}
		if (ft_strchr_gnl(s[fd], '\n'))
			break ;
	}
	return (return_value(fd, n_bytes, s, line));
}

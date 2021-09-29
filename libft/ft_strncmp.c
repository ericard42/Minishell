/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericard <ericard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:03:59 by addubois          #+#    #+#             */
/*   Updated: 2021/06/04 13:36:02 by ericard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr2;

	i = 0;
	ptr = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (i < n && *ptr && *ptr2)
	{
		if (*ptr != *ptr2)
		{
			return ((int)(*ptr - *ptr2));
		}
		ptr++;
		ptr2++;
		i++;
	}
	if (*ptr != *ptr2 && i != n)
		return (*ptr - *ptr2);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;

	ptr = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (*ptr && *ptr2)
	{
		if (*ptr != *ptr2)
		{
			return ((int)(*ptr - *ptr2));
		}
		ptr++;
		ptr2++;
	}
	if (*ptr != *ptr2)
		return (*ptr - *ptr2);
	return (0);
}

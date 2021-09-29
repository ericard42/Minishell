/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericard <ericard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:04:45 by addubois          #+#    #+#             */
/*   Updated: 2021/06/04 13:29:50 by ericard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	unsigned const char		*ptr;
	unsigned const char		*ptr2;

	i = 0;
	ptr = (unsigned const char *)s1;
	ptr2 = (unsigned const char *)s2;
	while (i < n)
	{
		if (*ptr != *ptr2)
		{
			return ((int)(*ptr - *ptr2));
		}
		ptr++;
		ptr2++;
		i++;
	}
	return (0);
}

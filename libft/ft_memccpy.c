/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addubois <addubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:04:50 by addubois          #+#    #+#             */
/*   Updated: 2021/07/04 11:42:02 by addubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr2;

	i = 0;
	ptr = (unsigned char *)src;
	ptr2 = (unsigned char *)dst;
	while (i < n)
	{
		*ptr2 = *ptr;
		if (*ptr == (unsigned char)c)
		{
			dst += i + 1;
			return (dst);
		}
		i++;
		ptr++;
		ptr2++;
	}
	dst = NULL;
	return (dst);
}

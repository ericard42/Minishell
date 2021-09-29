/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericard <ericard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:48:23 by addubois          #+#    #+#             */
/*   Updated: 2021/06/04 13:30:18 by ericard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;

	ptr = (unsigned char *)src;
	ptr2 = (unsigned char *)dst;
	if (ptr2 > ptr)
	{
		while (len--)
			ptr2[len] = ptr[len];
	}
	else
		ft_memcpy(ptr2, ptr, len);
	return (dst);
}

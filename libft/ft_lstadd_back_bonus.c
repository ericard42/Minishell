/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericard <ericard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:41:46 by addubois          #+#    #+#             */
/*   Updated: 2021/06/04 13:26:06 by ericard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*begin;

	begin = *lst;
	if (begin == NULL)
		*lst = new;
	else
	{
		while (begin->next)
			begin = begin->next;
		begin->next = new;
		new->prev = begin;
	}
}

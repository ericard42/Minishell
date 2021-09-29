/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericard <ericard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:04:58 by addubois          #+#    #+#             */
/*   Updated: 2021/06/04 13:27:54 by ericard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new;
	t_list	*aux;

	if (lst)
	{
		new = ft_lstnew(f(lst->content));
		aux = new;
		while (lst->next)
		{
			lst = lst->next;
			new->next = ft_lstnew(f(lst->content));
			if (!new->next)
			{
				del(new->next);
				free(new->next);
				return (NULL);
			}
			new = new->next;
		}
		return (aux);
	}
	return (NULL);
}

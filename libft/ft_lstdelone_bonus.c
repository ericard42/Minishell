/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addubois <addubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:05:05 by addubois          #+#    #+#             */
/*   Updated: 2021/06/14 11:37:03 by addubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdeletenode(t_list **head_ref, t_list *del)
{
	if (*head_ref == NULL || del == NULL)
		return ;
	if (*head_ref == del)
		*head_ref = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del);
	return ;
}

void	ft_lstdeleteall(t_list **head_ref)
{
	t_list	*head;

	head = *head_ref;
	if (*head_ref == NULL)
		return ;
	while (head)
	{
		ft_lstdeletenode(head_ref, head);
		head = *head_ref;
	}
}

void	ft_lstdeletenode_str(t_list2 **head_ref, t_list2 *del)
{
	if (*head_ref == NULL || del == NULL)
		return ;
	if (*head_ref == del)
		*head_ref = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	if (del->str != NULL)
		free(del->str);
	free(del);
	return ;
}

void	ft_lstdeleteall_str(t_list2 **head_ref)
{
	t_list2	*head;

	head = *head_ref;
	if (*head_ref == NULL)
		return ;
	while (head)
	{
		ft_lstdeletenode_str(head_ref, head);
		head = *head_ref;
	}
}

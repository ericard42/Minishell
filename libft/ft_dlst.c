/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addubois <addubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:48:13 by addubois          #+#    #+#             */
/*   Updated: 2021/07/04 12:06:09 by addubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	push(t_list **head_ref, int new_data)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	new_node->content = new_data;
	new_node->next = (*head_ref);
	new_node->prev = NULL;
	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;
	(*head_ref) = new_node;
}

void	append(t_list **head_ref, int new_data)
{
	t_list	*new_node;
	t_list	*last;

	new_node = (t_list *)malloc(sizeof(t_list));
	last = *head_ref;
	new_node->content = new_data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return ;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
	return ;
}

void	append_str(t_list2 **head_ref, char *new_data)
{
	t_list2	*new_node;
	t_list2	*last;

	new_node = (t_list2 *)malloc(sizeof(t_list2));
	last = *head_ref;
	new_node->str = ft_strdup(new_data);
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return ;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
	return ;
}

void	push_str(t_list2 **head_ref, char *new_data)
{
	t_list2	*new_node;

	new_node = (t_list2 *)malloc(sizeof(t_list2));
	new_node->str = ft_strdup(new_data);
	new_node->next = (*head_ref);
	new_node->prev = NULL;
	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;
	(*head_ref) = new_node;
}

void	insertAfter_str(t_list2 *prev_node, char *new_data)
{
	t_list2	*new_node;

	if (prev_node == NULL)
	{
		printf("the given previous node cannot be NULL");
		return ;
	}
	new_node = (t_list2 *)malloc(sizeof(t_list2));
	new_node->str = ft_strdup(new_data);
	new_node->next = prev_node->next;
	prev_node->next = new_node;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

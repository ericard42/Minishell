/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addubois <addubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:51:05 by addubois          #+#    #+#             */
/*   Updated: 2021/07/04 11:41:13 by addubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint_nbr(t_list *lst)
{
	while (lst != NULL)
	{
		ft_putnbr_fd(lst->content, 1);
		lst = lst->next;
		ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
}

void	ft_lstprint_str(t_list2 *lst2)
{
	int	i;

	i = 0;
	while (lst2 != NULL)
	{
		ft_putnbr_fd(i, 1);
		ft_putchar_fd(':', 1);
		ft_putstr_fd(lst2->str, 1);
		lst2 = lst2->next;
		ft_putchar_fd('\n', 1);
		i++;
	}
}

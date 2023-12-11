/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:29:54 by bcarolle          #+#    #+#             */
/*   Updated: 2023/11/06 10:05:48 by bcarolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (del == NULL || lst == NULL)
		return ;
	while ((*lst) != NULL)
	{
		temp = (*lst);
		(*lst) = (*lst)->next;
		ft_lstdelone(temp, del);
	}
}

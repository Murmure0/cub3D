/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 16:33:22 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/01 14:27:15 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cpy;

	if (!*lst)
		*lst = new;
	else
	{
		cpy = *lst;
		while (cpy->next)
		{
			cpy = cpy->next;
		}
		cpy->next = new;
	}
}

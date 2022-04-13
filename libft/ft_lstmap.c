/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 16:37:40 by cwastche          #+#    #+#             */
/*   Updated: 2021/08/01 15:19:08 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpy;
	t_list	*tmp;

	if (lst && f && del)
	{
		cpy = ft_lstnew(f(lst->content));
		if (!cpy)
			return (NULL);
		lst = lst->next;
		while (lst)
		{
			tmp = ft_lstnew(f(lst->content));
			if (!tmp)
			{
				ft_lstclear(&cpy, del);
				return (NULL);
			}
			ft_lstadd_back(&cpy, tmp);
			lst = lst->next;
		}
		return (cpy);
	}
	return (NULL);
}

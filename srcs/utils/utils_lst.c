/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/13 18:05:50 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

t_maillon	*new_maillon(char *line)
{
	t_maillon	*new;

	new = malloc(sizeof(t_maillon));
	if (!new)
		return (NULL);
	new->line = line;
	new->next = (void *)0;
	return (new);
}


int	ft_lstclear_empty(t_maillon *lst)
{
	t_maillon	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->line);
		free(lst);
		lst = tmp;
	}
	return (1);
}

void	ft_lstclear(t_maillon *lst)
{
	t_maillon	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

int	ft_lstsize(t_maillon *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


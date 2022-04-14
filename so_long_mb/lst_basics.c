/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:17:32 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/08 09:27:12 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_maillon	*new_maillon(char *line)
{
	t_maillon	*new;

	new = malloc(sizeof(t_maillon));
	if (!new)
		return (NULL);
	new->map_line = line;
	new->next = (void *)0;
	return (new);
}

int	ft_lstclear_empty(t_maillon *lst)
{
	t_maillon	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->map_line);
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

void	free_pars_map(t_map map)
{
	int	i;

	i = -1;
	while (++i < map.pars_height)
		free(map.pars_map[i]);
	free(map.pars_map);
}

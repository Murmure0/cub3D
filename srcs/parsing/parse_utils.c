/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:52:10 by cwastche          #+#    #+#             */
/*   Updated: 2022/04/20 11:52:12 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	spacedstrlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			i += 4;
		else
			i++;
	}
	return (i);
} 

int	convert_list_to_array(t_file *file)
{
	int		i;
	int		j;
	int		k;
	t_list	*tmp;

	if (check_for_newline(file->map))
		return (write(2, "Error\nEmpty line in map\n", 25), 1);
	i = 0;
	tmp = file->map;
	while (tmp)
	{
		file->scene[i] = malloc(sizeof(char) * (spacedstrlen(tmp->content) + 1));
		if (!file->scene[i])
			return (write(2, "Error\nMalloc failed.\n", 22), 1);
		j = -1;
		while (((char *)tmp->content)[++j])
		{
			if (((char *)tmp->content)[j] == '\t')
			{
				k = 0;
				while (k < 4)
				{
					file->scene[i][j++] = ' ';
					k++;
				}
			}
			else
				file->scene[i][j] = ((char *)tmp->content)[j];
		}
		file->scene[i][j] = 0;
		tmp = tmp->next;
		i++;
	}
	file->scene[i] = 0;
	return (0);
}

int	check_for_newline(t_list *map)
{
	t_list	*tmp;
	int i;

	tmp = map;
	i = 0;
	while (tmp)
	{
		i = parse_spaces((char *)tmp->content);
		if (((char *)tmp->content)[i] == 0 || ((char *)tmp->content)[0] == '\n')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	parse_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 9 || (str[i] >= 11 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

int	missing_param(t_p_nb p_nb)
{
	int	param_count;

	param_count = p_nb.c + p_nb.f + p_nb.ea + p_nb.no + p_nb.so + p_nb.we;
	if (param_count < 6)
		return (write(2, "Error\nMissing parameter\n", 25), 1);
	if (param_count > 6)
		return (write(2, "Error\nExcess parameters given\n", 25), 1);
	return (0);
}

void	free_param_chains(t_file *f, t_list *head)
{
	t_list	*tmp;

	while (f->map != head)
	{
		tmp = f->map->next;
		ft_lstdelone(f->map, free);
		f->map = tmp;
	}
}

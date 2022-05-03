/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:46:36 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/02 12:02:11 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	spacedstrlen(char *str)
{
	int	i;
	int	tab;

	i = -1;
	tab = 0;
	while (str[++i])
	{
		if (str[i] == '\t')
			tab++;
	}
	return (i + tab * 4 - tab);
}

static int	fill_str_with_spaces(t_file *file, int i, int k)
{
	int	j;

	j = 0;
	while (j < 4)
	{
		file->scene[i][k] = ' ';
		j++;
		k++;
	}
	return (j);
}

static int	fill_scene(t_file *file, t_list *tmp, int i)
{
	int		j;
	int		k;
	char	*str;

	str = tmp->content;
	file->scene[i] = malloc(sizeof(char) * (spacedstrlen(str) + 1));
	if (!file->scene[i])
		return (write(2, "Error\nMalloc failed.\n", 20), 1);
	j = -1;
	k = 0;
	while (str[++j])
	{
		if (str[j] == '\t')
			k += fill_str_with_spaces(file, i, k);
		else
		{
			file->scene[i][k] = str[j];
			k++;
		}
	}
	file->scene[i][j] = 0;
	return (0);
}

static int	check_for_newline(t_list *map)
{
	t_list	*tmp;
	char	*str;
	int		i;

	tmp = map;
	i = 0;
	while (tmp)
	{
		str = tmp->content;
		i = parse_spaces(str);
		if (str[i] == 0 || str[0] == '\n')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	free_scene(t_file *file, int i)
{
	while (file->scene[--i])
		free(file->scene[i]);
	free(file->scene);
}

int	convert_list_to_array(t_file *file)
{
	int		i;
	t_list	*tmp;

	if (check_for_newline(file->map))
		return (write(2, "Error\nEmpty line in map\n", 23), 1);
	i = 0;
	tmp = file->map;
	file->scene = malloc(sizeof(char *) * (ft_lstsize(file->map) + 1));
	if (!file->scene)
		return (write(2, "Error\nMalloc failed.\n", 21), 1);
	while (tmp)
	{
		if (fill_scene(file, tmp, i))
			return (free_scene(file, i), 1);
		tmp = tmp->next;
		i++;
	}
	file->scene[i] = 0;
	return (0);
}

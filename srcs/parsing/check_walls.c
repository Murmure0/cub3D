/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:43:36 by cwastche          #+#    #+#             */
/*   Updated: 2022/04/20 11:43:38 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	adj_line(char *line, int j)
{
	int	len;

	len = ft_strlen(line);
	if (len >= j)
	{
		if (is_space(line[j]))
			return (1);
	}
	else
		return (1);
	return (0);
}

static int	middle_lines(char **wall, int max_size)
{
	int	i;
	int	j;

	i = 0;
	while (wall[++i] && i < max_size)
	{
		if (check_left_wall(wall[i]) || check_right_wall(wall[i]))
			return (1);
		j = -1;
		while (wall[i][++j])
		{
			if (wall[i][j] == '0' || is_player(wall[i][j]))
			{
				if (j > 0)
				if (is_space(wall[i][j - 1]) || is_space(wall[i][j + 1]) || j == 0)
					return (1);
				if (adj_line(wall[i - 1], j) || adj_line(wall[i + 1], j))
					return (1);
			}
		}
	}
	return (0);
}

static int	last_line(char **wall, int i)
{
	int	j;

	j = -1;
	while (wall[i][++j])
	{
		if (wall[i][j] != '1' && is_space(wall[i][j]))
		 	return (1);
	}
	return (0);
}

static int	first_line(char **wall)
{
	int	x;

	x = -1;
	while (wall[0][++x])
	{
		if (wall[0][x] != '1' && !is_space(wall[0][x]))
			return (1);
	}
	return (0);
}

int	check_walls(t_file *file)
{
	if (first_line(file->scene)
		|| last_line(file->scene, ft_lstsize(file->map) - 1))
		return (write(2, "Error\nMap not walled in\n", 25), 1);
	if (middle_lines(file->scene, ft_lstsize(file->map) - 1))
		return (write(2, "Error\nMap not walled in\n", 25), 1);
	return (0);
}

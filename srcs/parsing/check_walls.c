/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:43:36 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/18 10:00:00 by mberthet         ###   ########.fr       */
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
				if (is_space(wall[i][j - 1]) || is_space(wall[i][j + 1]))
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
		if (wall[i][j] != '1' && !is_space(wall[i][j]))
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
	trim_nl_map_end(file->scene);
	if (first_line(file->scene)
		|| last_line(file->scene, arraylen(file->scene) - 1))
		return (write_ret("Error\nMap not walled in\n"));
	if (middle_lines(file->scene, arraylen(file->scene) - 1))
		return (write_ret("Error\nMap not walled in\n"));
	return (0);
}

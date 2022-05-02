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

// 212  Only checking 1 pos at the moment around spaces.
// 1 1  Might need to check 2 pos aswell ?
// 212
static int	check_around_space(char **wall, int i, int j)
{
	int	len;

	if (wall[i][j + 1] != '1' && !is_space(wall[i][j + 1])
		&& wall[i][j + 1] != 0 && wall[i][j + 1] != EOF)
		return (1);
	if (j > 0)
		if (wall[i][j - 1] != '1' && !is_space(wall[i][j - 1]))
			return (1);
	len = ft_strlen(wall[i + 1]);
	if (len > j)
		if (wall[i + 1][j] != '1' && !is_space(wall[i + 1][j])
			&& wall[i][j + 1] != 0 && wall[i][j + 1] != EOF)
			return (1);
	len = ft_strlen(wall[i - 1]);
	if (len > j)
		if (wall[i - 1][j] != '1' && !is_space(wall[i - 1][j])
			&& wall[i][j + 1] != 0 && wall[i][j + 1] != EOF)
			return (1);
	return (0);
}

static int	check_middle_lines(char **wall, int max_size)
{
	int	i;
	int	j;
	int	len_up;
	int	len_down;

	i = 0;
	while (wall[++i] && i < max_size)
	{
		j = -1;
		len_up = ft_strlen(wall[i - 1]);
		len_down = ft_strlen(wall[i + 1]);
		//NEED TO CHECK HERE WHEN LEN OF UPPER AND LOWER STR IS LONGER
		while (wall[i][++j])
		{
			if (wall[i][j] == ' ')
				if (check_around_space(wall, i, j))
					return (1);
		}
		if (len_up > j)
		{
			while (wall[i - 1][j])
			{
				if (wall[i - 1][j] != '1')
					return (1);
				j++;
			}
		}
		if (len_down > j)
		{
			while (wall[i + 1][j])
			{
				if (wall[i + 1][j] != '1')
					return (1);
				j++;
			}
		}
		if (check_left_wall(wall[i]) || check_right_wall(wall[i]))
			return (1);
	}
	return (0);
}

static int	check_last_line(char **wall, int i)
{
	int	j;
	int	k;
	int	len;

	j = -1;
	len = ft_strlen(wall[i - 1]);
	while (wall[i][++j])
	{
		if (is_space(wall[i][j]))
		{
			if (wall[i][j + 1] != '1' && !is_space(wall[i][j + 1])
				&& wall[i][j + 1] != 0 && wall[i][j + 1] != EOF)
				return (1);
			if (len >= j)
				if (wall[i - 1][j] != '1' && !is_space(wall[i - 1][j])
					&& wall[i - 1][j] != 0 && wall[i - 1][j] != EOF)
					return (1);
			if (len < j && wall[i][j] == '0')
				return (1);
		}
		else if (wall[i][j] != '1')
			return (1);
		k = j;
		if (len > k)
		{
			while (wall[i - 1][k])
			{
				if (wall[i - i][k] != '1')
					return (1);
				k++;
			}
		}
	}
	return (0);
}

static int	check_first_line(char **wall)
{
	int	x;
	int	len;

	x = -1;
	len = ft_strlen(wall[1]);
	while (wall[0][++x])
	{
		if (is_space(wall[0][x]))
		{
			if (wall[0][x + 1] != '1' && !is_space(wall[0][x + 1])
				&& wall[0][x + 1] != 0 && wall[0][x + 1] != EOF)
				return (1);
			if (len >= x)
				if (wall[1][x] != '1' && !is_space(wall[1][x])
					&& wall[1][x] != 0 && wall[1][x] != EOF)
					return (1);
		}
		else if (wall[0][x] != '1')
			return (1);
	}
	return (0);
}

int	check_walls(t_file *file)
{
	file->scene = malloc(sizeof(char *) * (ft_lstsize(file->map) + 1));
	if (!file->scene)
		return (write(2, "Error\nMalloc failed.\n", 22), 1);
	if (convert_list_to_array(file))
		return (1);
	if (check_first_line(file->scene)
		|| check_last_line(file->scene, ft_lstsize(file->map) - 1))
		return (write(2, "Error\nMap not walled in\n", 25), 1);
	if (check_middle_lines(file->scene, ft_lstsize(file->map) - 1))
		return (write(2, "Error\nMap not walled in\n", 25), 1);
	return (0);
}

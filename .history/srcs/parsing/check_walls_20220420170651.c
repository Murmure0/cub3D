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

static int	check_around_space(char **wall, int i, int j)
{
	int len;

	if (wall[i][j + 1] != '1' && wall[i][j + 1] != ' ' && wall[i][j + 1] != 0 && wall[i][j + 1] != EOF)
		return (1);
	if (j > 0)
		if (wall[i][j - 1] != '1' && wall[i][j - 1] != ' ')
			return (1);
	len = ft_strlen(wall[i + 1]);
	if (len >= j)
		if (wall[i + 1][j] != '1' && wall[i + 1][j] != ' ' && wall[i][j + 1] != 0 && wall[i][j + 1] != EOF)
			return (1);
	len = ft_strlen(wall[i - 1]);
	if (len >= j)
		if (wall[i - 1][j] != '1' && wall[i - 1][j] != ' ' && wall[i][j + 1] != 0 && wall[i][j + 1] != EOF)
			return (1);
	return (0);
}

//TOO LONG
//OVERFLOW WHEN ONLY WALLS
int	check_left_wall(char *str)
{
	int	wall;
	int i;

	wall = 0;
	i = parse_spaces(str);
	while (str[i])
	{
		if (str[i] != '1' && wall == 0) //&& str[i] != 0 && str[i] != '\n'
			return (1);
		else
			wall = 1;
		i++;
	}
	printf("LEFT OK\n");
	return (0);
}

int	check_right_wall(char *str)
{
	int	wall;
	int i;

	i = ft_strlen(str);
	wall = 0;
	while (i >= 0)
	{
		if (str[i] != '1' && wall == 0)
			return (printf("CHECK RIGHT\n"),1);
		else
			wall = 1;
		--i;
	}
	printf("RIGHT OK\n");
	return (0);
}

static int	check_middle_lines(char **wall, int max_size)
{
	int i;
	int j;

	i = 0;
	while (wall[++i] && i < max_size)
	{
		j = -1;
		while (wall[i][++j])
		{
			if (wall[i][j] == ' ')
				if (check_around_space(wall, i, j))
					return (printf("TEST\n"), 1);
		}
		printf("sent string: %s\n", wall[i]);
		if (check_left_wall(wall[i]) || check_right_wall(wall[i])) //PARSING NOT OK, RETURNS 1
			return (1);
	}
	return (0);
}

static int check_last_line(char **wall, int i)
{
	int j;
	int	len;

	j = -1;
	len = ft_strlen(wall[i - 1]);
	while (wall[i][++j])
	{
		if (wall[i][j] == ' ')
		{
			if (wall[i][j + 1] != '1' && wall[i][j + 1] != ' '
				&& wall[0][j + 1] != 0 && wall[0][j + 1] != EOF)
				return (1);
			if (len >=j)
				if 	(wall[i - 1][j] != '1' && wall[i - 1][j] != ' '
					&& wall[1][j] != 0 && wall[1][j] != EOF)
					return (1);
		}
		else if (wall[i][j] != '1')
			return (1);
	}
	return (0);
}

static int check_first_line(char **wall)
{
	int j;
	int	len;

	j = -1;
	len = ft_strlen(wall[1]);
	while (wall[0][++j])
	{
		if (wall[0][j] == ' ')
		{
			if (wall[0][j + 1] != '1' && wall[0][j + 1] != ' '
				&& wall[0][j + 1] != 0 && wall[0][j + 1] != EOF)
				return (1);
			if (len >= j)
				if (wall[1][j] != '1' && wall[1][j] != ' '
					&& wall[1][j] != 0 && wall[1][j] != EOF)
					return (1);
		}
		else if (wall[0][j] != '1')
			return (1);
	}
	return (0);
}

int	not_walled_in(t_file *file)
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

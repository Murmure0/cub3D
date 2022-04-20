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

#include ""

int check_first_line(char **wall)
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
				&& wall[0][j + 1] != '\n' && wall[0][j + 1] != EOF)
				return (1);
			if (len >= j)
				if (wall[1][j] != '1' && wall[1][j] != ' '
					&& wall[1][j] != '\n' && wall[1][j] != EOF)
					return (1);			
		}
		else if (wall[0][j] != '1')
			return (1);
	}
	return (0);
}

int check_last_line(char **wall, int i)
{
	int j;

	j = -1;
	while (wall[i][++j])
	{
		if (wall[i][j] == ' ')
		{
			if ((wall[i][j + 1] != '1' && wall[i][j + 1] != ' ')
				|| (wall[i - 1][j] != '1' && wall[i - 1][j] != ' '))
				return (1);
		}
		else if (wall[i][j] != '1')
			return (1);
	}
	return (0);
}

int	check_around_space(char **wall, int i, int j)
{
	int len;

	if (wall[i][j + 1] != '1' && wall[i][j + 1] != ' ' && wall[i][j + 1] != '\n' && wall[i][j + 1] != EOF)
		return (1);
	if (j > 0)
		if (wall[i][j - 1] != '1' && wall[i][j - 1] != ' ')
			return (1);
	len = ft_strlen(wall[i + 1]);
	if (len >= j)
		if (wall[i + 1][j] != '1' && wall[i + 1][j] != ' ' && wall[i][j + 1] != '\n' && wall[i][j + 1] != EOF)
			return (1);
	len = ft_strlen(wall[i - 1]);
	if (len >= j)
		if (wall[i - 1][j] != '1' && wall[i - 1][j] != ' ' && wall[i][j + 1] != '\n' && wall[i][j + 1] != EOF)
			return (1);
	return (0);
}

//TOO LONG
int	check_middle_lines(char **wall, int max_size)
{
	int i;
	int j;
	int	l_wall;
	int	r_wall;

	i = 0;
	l_wall = 0;
	while (wall[++i] && i < max_size)
	{
		j = -1;
		while (wall[i][++j])
		{
			if (wall[i][j] == ' ')
			{
				if (check_around_space(wall, i, j))
					return (1);
			}
			else if (wall[i][j] != '1' && l_wall == 0)
				return (1);
			else
				l_wall = 1;
		}
		while (wall[i][--j])
		{
			if (wall[i][j] == ' ')
				continue ;
			if (wall[i][j] != '1' && r_wall == 0)
				return (1);
			else
				r_wall = 1;
		}
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
		return (1);
	 if (check_middle_lines(file->scene, ft_lstsize(file->map) - 1))
	 	return (1);
	
	return (0);
}

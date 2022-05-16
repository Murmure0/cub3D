/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:52:10 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/02 10:06:07 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		return (write(2, "Error\nMissing parameter\n", 23), 1);
	else if (param_count > 6)
		return (write(2, "Error\nExcess parameters given\n", 29), 1);
	return (0);
}

void	convert_space_to_wall(char **map)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (is_space(map[y][x]))
				map[y][x] = '1';
		}
	}
}

void	free_params(t_file *file)
{
	ft_lstclear(&file->map, free);
	free(file->param->no);
	free(file->param->so);
	free(file->param->we);
	free(file->param->ea);
}

void	init_map_size(t_file *file)
{
	int	i;

	i = 0;
	while (file->scene[i])
		i++;
	file->map_h = i;
	file->map_w = ft_strlen(file->scene[0]);
}

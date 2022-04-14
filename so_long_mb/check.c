/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:13:27 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/09 16:15:58 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	wrg_wall(void)
{
	write(2, "Something is wrong with the wall.\n", 35);
	return (0);
}

static int	check_wall(char **pars_map, t_map map)
{
	int	i;
	int	j;
	int	height;
	int	length;

	i = -1;
	j = -1;
	height = (map.pars_height - 1);
	length = (map.pars_width - 1);
	while (pars_map[0][++i] != '\0')
		if (pars_map[0][i] != '1')
			return (wrg_wall());
	i = -1;
	while (pars_map[height][++i] != '\0')
		if (pars_map[height][i] != '1')
			return (wrg_wall());
	while (++j <= height)
		if (pars_map[j][0] != '1')
			return (wrg_wall());
	j = -1;
	while (++j <= height)
		if (pars_map[j][length] != '1')
			return (wrg_wall());
	return (1);
}

static int	check_collectible(char **pars_map, t_map map)
{
	if (find_stuff(pars_map, 'C', map) && find_stuff(pars_map, 'E', map)
		&& find_stuff(pars_map, 'P', map))
		return (1);
	return (0);
}

static int	check_wrg_stuff(char **pars_map, t_map map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map.pars_height)
	{
		i = 0;
		while (pars_map[j][i] != '\0')
		{
			if (pars_map[j][i] != '1' && pars_map[j][i] != '0'
			&& pars_map[j][i] != 'C' && pars_map[j][i] != 'E'
			&& pars_map[j][i] != 'P')
			{
				write(2, "Wrong component on the map.\n", 29);
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

int	valid_map(char **pars_map, t_map map)
{
	if (!check_wall(pars_map, map) ||!check_collectible(pars_map, map)
		|| !check_wrg_stuff(pars_map, map))
		return (0);
	return (1);
}

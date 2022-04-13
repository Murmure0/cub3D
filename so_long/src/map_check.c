/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:21:57 by cwastche          #+#    #+#             */
/*   Updated: 2022/02/04 09:23:15 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/so_long.h"

static int	lenght_check(char **map)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(map[0]);
	while (map[++i])
	{
		if (len != ft_strlen(map[i]))
			return (1);
	}
	return (0);
}

static int	walls_check(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		if (i == 0 || !map[i + 1])
		{
			j = 0;
			while (map[i][j])
			{
				if (!ft_strrchr("1", map[i][j++]))
					return (1);
			}
		}
		else
		{
			if (!ft_strrchr("1", map[i][0]) ||
				!ft_strrchr("1", map[i][ft_strlen(map[i]) - 1]))
				return (1);
		}
	}
	return (0);
}

static int	symbols_check(t_data *var)
{
	int	i;
	int	j;

	i = 0;
	while (var->map[i])
	{
		j = 0;
		while (var->map[i][j])
		{
			if (var->map[i][j] == 'E')
				var->e += 1;
			if (var->map[i][j] == 'P')
				var->p += 1;
			if (var->map[i][j] == 'C')
				var->c += 1;
			if (!ft_strrchr("01CEP", var->map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	map_check(t_data *var)
{
	var->p = 0;
	var->c = 0;
	var->e = 0;
	if (walls_check(var->map))
		error("Map not walled in.", var);
	if (symbols_check(var))
		error("Forbidden character used in chosen map file.", var);
	if (lenght_check(var->map))
		error("Chosen map is not a rectangle.", var);
	if (var->e != 1)
		error("More or less than 1 exit detected.", var);
	if (var->p != 1)
		error("More or less than 1 player detected.", var);
	if (var->c <= 0)
		error("No collectible detected.", var);
}

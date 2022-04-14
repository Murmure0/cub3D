/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:12:10 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/10 10:55:54 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_mini_map(int fd, t_map *map, t_maillon *lst_gnl_map)
{
	map->pars_height = ft_lstsize(lst_gnl_map);
	map->pars_width = ft_strlen(lst_gnl_map->map_line);
	if (((map->pars_width < 3 && map->pars_height < 5) || (map->pars_width < 3
				&& map->pars_height < 5)) && ft_lstclear_empty(lst_gnl_map))
	{
		write(2, "Map way too small.\n", 20);
		close(fd);
		return (0);
	}
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		write(2, "Wrong argument number.\n", 24);
		return (0);
	}
	i = ft_strlen(argv[1]);
	if (argv[1][--i] == 'r' && argv[1][--i] == 'e' && argv[1][--i] == 'b'
	&& argv[1][--i] == '.')
		return (1);
	write(2, "Map is not .ber\n", 17);
	return (0);
}

void	*wr_err_empt(void)
{
	write(2, "Empty map.\n", 12);
	return (NULL);
}

void	*wr_err_size(void)
{
	write(2, "Line size problem.\n", 20);
	return (NULL);
}

int	find_stuff(char **pars_map, char stuff, t_map map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map.pars_height)
	{
		i = 0;
		while (pars_map[j][i] != '\0')
		{
			if (pars_map[j][i] == stuff)
				return (1);
			i++;
		}
		j++;
	}
	write(2, "Some component(s) is/are missing on the map.\n", 46);
	return (0);
}

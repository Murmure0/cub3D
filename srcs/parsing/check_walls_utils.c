/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche </var/mail/cwastche>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:46:13 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/10 23:27:08 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_space(char c)
{
	if (c == 9 || (c >= 11 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	check_left_wall(char *str)
{
	int	wall;
	int	i;

	wall = 0;
	i = parse_spaces(str);
	while (str[i])
	{
		if (str[i] != '1' && wall == 0)
			return (1);
		else
			wall = 1;
		i++;
	}
	return (0);
}

int	check_right_wall(char *str)
{
	int	wall;
	int	i;

	i = ft_strlen(str);
	wall = 0;
	while (--i >= 0)
	{
		if (str[i] == ' ')
			continue ;
		if (str[i] != '1' && wall == 0)
			return (1);
		else
			wall = 1;
	}
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	trim_nl_map_end(char **map)
{
	int		i;
	char	**tmp;

	tmp = map;
	i = arraylen(tmp);
	i--;
	while (i >= 0 && tmp[i])
	{
		if (tmp[i][0] == '\n')
		{
			tmp[i] = 0;
			free(tmp[i]);
		}
		else
			break ;
		i--;
	}
}

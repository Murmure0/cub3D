/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:15:53 by cwastche          #+#    #+#             */
/*   Updated: 2022/04/15 18:52:33 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_chars_used(t_list *map)
{
	t_list	*tmp;
	char	*s;
	int		i;
	int		player_count;

	tmp = map;
	player_count = 0;
	while (tmp)
	{
		s = tmp->content;
		i = -1;
		while (s[++i])
		{
			if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
				player_count++;
			if (s[i] != '0' && s[i] != '1' && s[i] != 'N' && s[i] != 'S' 
				&& s[i] != 'E' && s[i] != 'W'
				&& !is_space(s[i]) && s[i] != '\n')
				return (write(2, "Error\nForbidden char in map\n", 28), 1);
		}
		tmp = tmp->next;
	}
	if (player_count != 1)
		return (write(2, "Error\nWrong nb of player\n", 24), 1);
	return (0);
}

static int	check_map(t_file *file)
{
	if (ft_lstsize(file->map) < 3)
		return (write(2, "Error\nMap too small\n", 20), 1);
	if (check_chars_used(file->map))
		return (1);
	if (check_walls(file))
		return (1);
	return (0);
}

static int	check_file(int ac, char **av)
{
	if (ac != 2)
		return (write(2, "Error\nArgument invalid.\n", 24), 1);
	if (ft_strncmp(".cub", &av[1][ft_strlen(av[1]) - 4], 4))
		return (write(2, "Error\nWrong extension file.\n", 28), 1);
	return (0);
}

static int	read_file(int fd, t_file *file)
{
	t_list	*chain;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (write(2, "Error\nEmpty file.\n", 18), 1);
	file->map = ft_lstnew(line);
	if (!file->map)
		return (write(2, "Error\nMalloc failed.\n", 22), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		chain = ft_lstnew(line);
		if (!chain)
		{
			write(2, "Error\nMalloc failed.", 22);
			return (ft_lstclear(&file->map, free), 1);
		}
		ft_lstadd_back(&file->map, chain);
	}
	return (0);
}

int	parse_file(t_file *file, int ac, char **av)
{
	int	fd;

	if (check_file(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nOpen"), 1);
	if (read_file(fd, file))
		return (1);
	join_split_params(file);
	if (check_params(file))
		return (1);
	if (check_map(file))
		return (1);
	return (0);
}

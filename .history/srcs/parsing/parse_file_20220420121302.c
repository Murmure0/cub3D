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

static int	forbidden_char_found(t_list *map)
{
	t_list	*tmp;
	char	*str;
	int		i;

	tmp = map;
	while (tmp)
	{
		i = -1;
		str = (char *)tmp->content;
		while (str[++i])
		{
			if (str[i] != '0' && str[i] != '1' && str[i] != 'N'
				&& str[i] != 'S' && str[i] != 'E'
				&& str[i] != 'W' && str[i] != ' ' && str[i] != '\n')
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	check_map(t_file *file)
{
	if (ft_lstsize(file->map) < 3)
		return (write(2, "Error\nMap too small\n", 21), 1);
	if (forbidden_char_found(file->map))
		return (write(2, "Error\nForbidden char in map\n", 29), 1);
	if (not_walled_in(file))
		return (write(2, "Error\nMap not walled in\n", 25), 1);
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

static int	check_file(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (write(2, "Error\nArgument invalid.\n", 24), 1);
	if (ft_strncmp(".cub", &av[1][ft_strlen(av[1]) - 4], 4))
		return (write(2, "Error\nWrong extension file.\n", 28), 1);
	return (0);
}

int parse_file(t_file *file, int ac, char **av)
{
	int	fd;

	if (check_file(ac, av))
		return (1);
 	fd = open(av[1], O_RDONLY);
 	if (fd < 0)
 		return (perror("Error\nOpen"), 1);
 	if (read_file(fd, file))
 		return (1);
	if (check_params(file))
		return (1);
 	 if (check_map(file))
	 	return (1);
	return (0);
}

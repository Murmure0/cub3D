/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:15:53 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/18 10:30:44 by mberthet         ###   ########.fr       */
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
				return (write_ret("Error\nForbidden char in map\n"));
		}
		tmp = tmp->next;
	}
	if (player_count != 1)
		return (write_ret("Error\nWrong nb of player\n"));
	return (0);
}

static int	check_map(t_file *file)
{
	if (ft_lstsize(file->map) < 3)
		return (write_ret("Error\nMap too small\n"));
	else if (check_chars_used(file->map) || convert_list_to_array(file)
		|| check_walls(file))
		return (1);
	return (0);
}

static int	is_ascii(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] > 127 || str[i] < 0)
			return (0);
	}
	return (1);
}

static int	creat_lst(char *line, t_list *lst, int fd, t_file *file)
{
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_ascii(line))
			return (write_ret("Error\nNon ascii char found\n"));
		lst = ft_lstnew(line);
		if (!lst)
		{
			ft_lstclear(&file->map, free);
			return (write_ret("Error\nMalloc failed\n"));
		}
		ft_lstadd_back(&file->map, lst);
	}
	return (0);
}




static int	read_file_to_lst(int fd, t_file *file)
{
	t_list	*lst;
	char	*line;

	lst = NULL;
	line = get_next_line(fd);
	if (!line)
		return (write_ret("Error\nEmpty file\n"));
	if (!is_ascii(line))
		return (write_ret("Error\nNon ascii char found\n"));
	file->map = ft_lstnew(line);
	if (!file->map)
	{
		free(line);
		return (write_ret("Error\nMalloc failed\n"));
	}
	if (creat_lst(line, lst, fd, file))
		return (1);
	close(fd);
	return (0);
}

int	parse_file(t_file *file, int ac, char **av)
{
	int	fd;

	dir_params_to_null(file);
	if (ac != 2)
		return (write_ret("Error\nArgument invalid\n"));
	if (ft_strncmp(".cub", &av[1][ft_strlen(av[1]) - 4], 4))
		return (write_ret("Error\nWrong extension file\n"));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nOpen"), 1);
	if (read_file_to_lst(fd, file))
		return (close(fd), 1);
	if (join_split_params(file) || check_params(file)
		|| check_map(file) || fill_map(file->scene))
		return (free_params(file), 1);
	init_map_size(file);
	ft_lstclear(&file->map, free);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:58 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/13 18:02:54 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static int check_file(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		write(2, "Error\nArgument invalid.\n", 24);
		return(1);
	}
	if (ft_strncmp(".cub", &av[1][ft_strlen(av[1]) - 4], 4))
	{
		write(2, "Error\nWrong extension file.\n", 28);
		return(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nAccess to the file denied.\n", 33);
		return(1);
	}
	close (fd);
	return (0);
}

static void	init(t_maillon *tmp, t_maillon *first, char *line)
{
	line[ft_strlen(line) - 1] = '\0';
	first = new_maillon(line);
	if (!first)
	{
		free(line);
		exit(0);
	}
	tmp = first;
}

t_maillon *get_map(int fd)
{
	char		*line;
	t_maillon	*first;
	t_maillon	*tmp;

	first = NULL;
	tmp = NULL;
	line = get_next_line(fd);
	if(!line)
	{
		write(2, "Error\nEmpty file.\n", 18);
		return (NULL);
	}
	init(tmp, first, line);
	while(line)
	{
		//printf("%s", line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		tmp->next = new_maillon(line); //sgfault
		if (!tmp->next && ft_lstclear_empty(first))
			return (NULL);
		tmp = tmp->next;
	}
	tmp->next = NULL;
	free(line);
	return (first);
}

int parse_file(t_file *file, int ac, char **av)
{
	(void)file;
	int			fd;
	t_maillon	*lst_gnl_map;

	if (check_file(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	// lst_gnl_map = get_map(fd); //segfault D:
	// if (!lst_gnl_map)
	// {
	// 	close(fd);
	// 	return (1);
	// }
	close (fd);
	return (0);
}
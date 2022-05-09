/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:13:47 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/09 16:22:12 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init(t_maillon **tmp, t_maillon **first, char *line, int *length)
{
	line[ft_strlen(line) - 1] = '\0';
	*first = new_maillon(line);
	if (!*first)
	{
		free(line);
		exit(0);
	}
	*length = ft_strlen(line);
	*tmp = *first;
}

static t_maillon	*creatlist(int fd, t_maillon *tmp)
{
	t_maillon	*first;
	char		*line;
	int			length;

	line = get_next_line(fd);
	if (!line)
		return (wr_err_empt());
	init(&tmp, &first, line, &length);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		tmp->next = new_maillon(line);
		if (!tmp->next && ft_lstclear_empty(first))
			return (NULL);
		if (ft_strlen(line) != length && ft_lstclear_empty(first))
			return (wr_err_size());
		tmp = tmp->next;
	}
	tmp->next = (void *)0;
	return (first);
}

static char	**creat_pars_map(t_maillon *lst_gnl_map, t_map *map, int fd)
{
	char		**pars_map;
	t_maillon	*tmp;
	int			i;

	i = 0;
	pars_map = malloc(sizeof(char *) * map->pars_height);
	if (!pars_map && ft_lstclear_empty(lst_gnl_map))
	{
		close(fd);
		return (NULL);
	}
	tmp = lst_gnl_map;
	while (tmp)
	{
		pars_map[i++] = tmp->map_line;
		tmp = tmp->next;
	}
	return (pars_map);
}

char	**read_map(int argc, char **argv, t_map *map)
{
	int			fd;
	char		**pars_map;
	t_maillon	*lst_gnl_map;
	t_maillon	*tmp;

	tmp = NULL;
	if (!check_arg(argc, argv))
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	lst_gnl_map = creatlist(fd, tmp);
	if (!lst_gnl_map)
	{
		close(fd);
		return (NULL);
	}
	if (!check_mini_map(fd, map, lst_gnl_map))
		return (NULL);
	pars_map = creat_pars_map(lst_gnl_map, map, fd);
	if (!pars_map)
		return (NULL);
	close(fd);
	ft_lstclear(lst_gnl_map);
	return (pars_map);
}

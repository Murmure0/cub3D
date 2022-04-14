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
		return (write(2, "Error\nArgument invalid.\n", 24), 1);
	if (ft_strncmp(".cub", &av[1][ft_strlen(av[1]) - 4], 4))
		return (write(2, "Error\nWrong extension file.\n", 28), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nOpen"), 1);
	close (fd);
	return (0);
}
/*
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
}*/

/* == read_file()
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
*/
/*





int	not_walled_in()
{
	check_first_line();
	check_first_and_last_char();
	check_last_line();
	if (error)
		return (1);
	return (0);
}

int	check_map(t_list *map)
{
	if (forbidden_char_found()) //parse a travers tout, on verif tous les chars utilises
		// Eventuellement check if plus de 1 player starting position, a discuter (soit on error, soit on en garde 1 et le reste = floor)
		//error, free, etc...
	if (not_walled_in()) //verif les walls
		//error
	if (error)
		return (1);
	return (0);
}
*/

int	parse_spaces(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

void	free_param_chains(t_list *list, t_list *head)
{
	t_list *tmp;

	while (list != head)
	{
		tmp = list->next;
		ft_lstdelone(list, free);
		list = tmp;
	}
}

int	map_is_found(t_file *file, t_list *tmp, int i)
{
	char c;

	c = ((char *)tmp->content)[i];
	if (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (free_param_chains(file->map, tmp), 1);
	return (0);
}

void fill_color(char *str, int *color)
{
	(void)str;
	(void)color;
}

void fill_texture(char *str, char *texture)
{
	(void)str;
	(void)texture;
}

int param_id_found(t_list *tmp, int i, t_file *file)
{
	char *str;

	str = (char *)tmp->content;
	if (str[i] == 'C')
		return (fill_color(file->map->content, &file->param.ceiling), 1);
	else if (str[i] == 'F')
		return (fill_color(file->map->content, &file->param.floor), 1);
	else if (str[i] == 'N' && str[i + 1] == 'O')
		return (fill_texture(file->map->content, file->param.no), 1);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (fill_texture(file->map->content, file->param.so), 1);
	else if (str[i] == 'E' && str[i] == 'A')
		return (fill_texture(file->map->content, file->param.ea), 1);
	else if (str[i] == 'W' && str[i] == 'E')
		return (fill_texture(file->map->content, file->param.we), 1);
	return (0);
}



int	missing_param(t_params param)
{
	//Verif données ? Arborescence de msgs d'erreur ?
	if (!param.no || param.so || param.we || param.ea
		|| param.ceiling || param.floor)
		return (1);
	return (0);
}

int	check_params(t_file *file)
{
	t_list	*tmp;
	int		i;
	
	tmp = file->map;
	while (tmp)
	{
		i = 0;
		i += parse_spaces(tmp->content);
		if (((int)tmp->content[i] == '\n')
		{
			tmp = tmp->next;
			continue ;
		}
		if (map_is_found(file, tmp, i))
			break ;
		else if (param_id_found(tmp, i, file))
			tmp = tmp->next;
		else
			return(write(2, "Error\nFile not acceptable\n", 27), 1);
	}
	if (missing_param(file->param))
		return(write(2, "Error\nMissing parameter\n", 27), 1); 
	return (0);
}

int	read_file(int fd, t_file *file)
{
	t_list	*chain;
	char	*line;

	line = get_next_line(fd);
	if(!line)
		return (write(2, "Error\nEmpty file.\n", 18), 1);
	file->map = ft_lstnew(line);
	if (!file->map)
		return (write(2, "Error\nMalloc failed.\n", 22), 1);
	while(1)
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
	//FOR TESTING PURPOSES, TO DEL
	// while (file->map)
	// {
	// 	printf("%s", file->map->content);
	// 	file->map = file->map->next;
	// }
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
	check_params(file);
// 	check_map(file->map); //Verif map

// //	map is ok
// 	init_minilibx() 
	//On retape so_long pour la minilibx pour commencer
	//Events handler pour quiter et se deplacer sont identiques

	//Je crois que floor + ceiling seront des pixels colores, donc utiliser put_pixel
	//WIP pour la 3D et tourner le apt de vue
	


	//segfault D:
	// if (!lst_gnl_map)
	// {
	// 	close(fd);
	// 	return (1);
	// }
	// close (fd);
	return (0);
}
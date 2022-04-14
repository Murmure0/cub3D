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

int	map_is_found(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

void fill_color(char *str, int *color)
{

}

void fill_texture(char *str, char *texture)
{

}

int param_id_found(char c, t_file *file)
{
	if (c == 'C')
		return (fill_color(file->map->content, &file->param.c), 1);
	else if (c == 'F')
		return (fill_color(file->map->content, &file->param.f), 1);
	else if (c == 'NO')
		return (fill_texture(file->map->content, file->param.no), 1)
	else if (c == 'SO')
		return (fill_texture(file->map->content, file->param.so), 1)
	else if (c == 'EA')
		return (fill_texture(file->map->content, file->param.ea), 1)
	else if (c == 'WE')
		return (fill_texture(file->map->content, file->param.we), 1)
	return (0);
}

int	check_params(t_file *file)
{
	t_list	*tmp;
	int		i;
	int		j;
	
	tmp = file->map;
	j = 0;
	while (tmp)
	{
		i = 0;
		i += parse_spaces(tmp->content);
		if (tmp->content[i] == '\n')
		{
			tmp = tmp->next;
			j++;
			continue ;
		}
		if (map_is_found(tmp->content[i]))
		{

			file->map = tmp; fct to free remaining lists?
			// free() previous lists;
			break;
		}
		else if (param_id_found(tmp->content[i]), file))
			tmp = tmp->next;
		else
			return(write(2, "Error\nFile not acceptable\n", 27), 1);
		j++;
	}
	if (missing_param()) //check si l'un des param n'est pas donne
		error msg;
	if (error)
		return (1);
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
	(void)file;

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
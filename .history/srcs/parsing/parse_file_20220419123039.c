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

int check_first_line(char **wall)
{
	int j;

	j = -1;
	while (wall[0][++j])
	{
		if (wall[0][j] == ' ')
		{
			if ((wall[0][j + 1] != '1' || wall[0][j + 1] != ' ')
			|| (wall[1][j] != '1' || wall[1][j] != ' '))
				return (1);
		}
		else if (wall[0][j] != '1')
			return (1);
	}
	return (0);
}

int check_last_line(char **wall, int i)
{
	int j;

	j = -1;
	while (wall[i][++j])
	{
		if (wall[i][j] == ' ')
		{
			if ((wall[i][j + 1] != '1' && wall[i][j + 1] != ' ')
				|| (wall[i - 1][j] != '1' && wall[i - 1][j] != ' '))
				return (1);
		}
		else if (wall[i][j] != '1')
			return (1);
	}
	return (0);
}

int	convert_list_to_array(t_file *file)
{
	int		i;
	int		j;
	t_list	*tmp;

	//CHECK FOR \n IN MAP
	i = 0;
	tmp = file->map;
	while (tmp)
	{
		file->scene[i] = malloc(sizeof(char) * (ft_strlen(tmp->content) + 1));
		if (!file->scene[i])
			return (write(2, "Error\nMalloc failed.\n", 22), 1);
		j = -1;
		while (((char *)tmp->content)[++j])
			file->scene[i][j] = ((char *)tmp->content)[j];
		file->scene[i][j] = 0;
		tmp = tmp->next;
		i++;
	}
	file->scene[i] = 0;
	return (0);
}

int	check_around_space(char **wall, int i, int j)
{
	if (i > 0)
	
	if ((wall[i][j + 1] != '1' && wall[i][j + 1] != ' ')
		return (1);
	else if (wall[i - 1][j] != '1' && wall[i - 1][j] != ' '))
		return (1);

	return (0);
}

int	check_middle_lines(char **wall, int max_size)
{
	int i;
	int j;

	i = 0;
	while (wall[++i] && i < max_size)
	{
		j = -1;
		while (wall[i][++j])
		{
			if (wall[i][j] == ' ')
				if (check_around_space(wall, i, j))
					return (1);
		}
	}
}

//SPACE == EMPTY, MUST BE CLOSED BY WALLS
int	not_walled_in(t_file *file)
{
	file->scene = malloc(sizeof(char *) * (ft_lstsize(file->map) + 1));
	if (!file->scene)
		return (write(2, "Error\nMalloc failed.\n", 22), 1);
	convert_list_to_array(file);
	if (check_first_line(file->scene)
		|| check_last_line(file->scene, ft_lstsize(file->map) - 1))
		return (1);
	if (check_middle_lines(file->scene, ft_lstsize(file->map) - 1))
		//error
	
	return (0);
}

int	forbidden_char_found(t_list *map)
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
				&& str[i] != 'W' && str[i] != ' ' && str[i] != 10)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_map(t_file *file)
{

	//ADD: IF LESS THAN 3 LINES OF MAP
	// ERROR MAP TOO SMALL
	if (forbidden_char_found(file->map))
		return (write(2, "Error\nForbidden char in map\n", 29), 1);
	if (not_walled_in(file))
		return (write(2, "Error\nMap not walled in\n", 25), 1);
	return (0);
}

int	parse_spaces(char *str)
{
	int i;

	i = 0;
	while (str[i] == 9 || (str[i] >= 11 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

void	free_param_chains(t_file *f, t_list *head)
{
	t_list *tmp;

	while (f->map != head)
	{
		tmp = f->map->next;
		ft_lstdelone(f->map, free);
		f->map = tmp;
	}
}

int	map_is_found(t_file *file, t_list *tmp, int i)
{
	char c;
	char d;

	c = ((char *)tmp->content)[i];
	d = ((char *)tmp->content)[i + 1];
	if (c == '0' || c == '1' || (c == 'N' && d != 'O') || (c == 'S' && d != 'O')
		|| (c == 'E' && d != 'A') || (c == 'W' && d != 'E'))
		return (free_param_chains(file, tmp), 1);
	return (0);
}

//CHECK COLOR && TEXTURE VALUES, RETURN ERROR IF BAD
void fill_color(char *str, int *color)
{
	(void)str;
	*color = 1;
}

void fill_texture(char *str, char **texture)
{
	int i;

	i = 2;
	i += parse_spaces(str + 2);
	*texture = ft_substr(str, i, ft_strlen(str));
	// if (ft_strncmp(".xpm", *texture[ft_strlen(*texture) - 4], 4))
	// 	return (write(2, "Error\nWrong texture extension.\n", 32), 1);
}

int param_id_found(t_list *tmp, int i, t_file *file)
{
	char *str;

	str = (char *)tmp->content;
	if (str[i] == 'C')
		return (fill_color(file->map->content, &file->param->ceiling), 1);
	else if (str[i] == 'F')
		return (fill_color(file->map->content, &file->param->floor), 1);
	else if (str[i] == 'N' && str[i + 1] == 'O')
		return (fill_texture(file->map->content, &file->param->no), 1);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (fill_texture(file->map->content, &file->param->so), 1);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (fill_texture(file->map->content, &file->param->ea), 1);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (fill_texture(file->map->content, &file->param->we), 1);
	return (0);
}

int	missing_param(t_params *param)
{
	// FOR TESTING PURPOSES, TO DEL
	// printf("%s\n", param->no);
	// printf("%s\n", param->so);
	// printf("%s\n", param->we);
	// printf("%s\n", param->ea);	
	// printf("%d\n", param->ceiling);
	// printf("%d\n", param->floor);
	if (!param->no || !param->so || !param->we || !param->ea
		|| !param->ceiling || !param->floor)
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
		if (((char *)tmp->content)[i] == '\n')
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
		return(write(2, "Error\nMissing parameter\n", 25), 1); 
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
	if (check_params(file))
		return (1);
 	 if (check_map(file)) //abort ici
	 	return (1);

// 	init_minilibx()
	//On retape so_long pour la minilibx pour commencer
	//Events handler pour quiter et se deplacer sont identiques

	//Je crois que floor + ceiling seront des pixels colores, donc utiliser put_pixel
	//WIP pour la 3D et tourner le apt de vue
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:57:09 by cwastche          #+#    #+#             */
/*   Updated: 2022/04/20 11:57:10 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//CHECK COLOR && TEXTURE VALUES, RETURN ERROR IF BAD
//RETURN INT PROB FOR ERROR MANAGEMENT, + change parsing to return errors...
static void	fill_color(char *str, int *color)  //TODO
{
	//COLOR RANGE: 0-255, LESS OR MORE = EXIT + CHECK IF ISDIGIT + GIVEN PARAM > max int ?
	
	//++str //skip C or F
	//parse_spaces()
	//split str, ','
	//if != 3 -> error
	//if values not 0-255 -> error
	//assign value
	(void)str;
	*color = 1;
}

static void	fill_texture(char *str, char **texture) //TODO
{
	int	i;

	i = 2;
	i += parse_spaces(str + 2);
	*texture = ft_substr(str, i, ft_strlen(str));
	//Maybe ?
	if (ft_strncmp(".xpm", &texture[0][ft_strlen(texture[0]) - 4], 4))
		write(2, "Error\nWrong texture extension.\n", 32);
}

static int	param_id_found(t_list *tmp, int i, t_file *file, t_p_nb *p_nb)
{
	char	*line;
	char	*str;

	str = (char *)tmp->content;
	line = (char *)file->map->content;
	if (str[i] == 'C')
		return (p_nb->c++, fill_color(line, &file->param->ceiling), 1);
	else if (str[i] == 'F')
		return (p_nb->f++, fill_color(line, &file->param->floor), 1);
	else if (str[i] == 'N' && str[i + 1] == 'O')
		return (p_nb->no++, fill_texture(line, &file->param->no), 1);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (p_nb->so++, fill_texture(line, &file->param->so), 1);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (p_nb->ea++, fill_texture(line, &file->param->ea), 1);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (p_nb->we++, fill_texture(line, &file->param->we), 1);
	return (0);
}

static int	map_is_found(t_file *file, t_list *tmp, int i)
{
	char	c;
	char	d;

	c = ((char *)tmp->content)[i];
	d = ((char *)tmp->content)[i + 1];
	if (c == '0' || c == '1' || (c == 'N' && d != 'O') || (c == 'S' && d != 'O')
		|| (c == 'E' && d != 'A') || (c == 'W' && d != 'E'))
		return (free_param_chains(file, tmp), 1);
	return (0);
}

void	param_count_init(t_p_nb *p_nb)
{
	p_nb->c = 0;
	p_nb->f = 0;
	p_nb->no = 0;
	p_nb->so = 0;
	p_nb->we = 0;
	p_nb->ea = 0;
}

int	check_params(t_file *file)
{
	t_list	*tmp;
	int		i;
	t_p_nb	p_nb;

	param_count_init(&p_nb);
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
		else if (param_id_found(tmp, i, file, &p_nb))
			tmp = tmp->next;
		else
			return (write(2, "Error\nFile not acceptable\n", 27), 1);
	}
	if (missing_param(p_nb))
		return (1);
	return (0);
}

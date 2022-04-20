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
static void	fill_color(char *str, int *color)
{
	(void)str;
	*color = 1;
}

static void	fill_texture(char *str, char **texture)
{
	int	i;

	i = 2;
	i += parse_spaces(str + 2);
	*texture = ft_substr(str, i, ft_strlen(str));
	//Maybe ?
	if (ft_strncmp(".xpm", texture[ft_strlen(*texture) - 4], 4))
		return (write(2, "Error\nWrong texture extension.\n", 32), 1);
}

static int	param_id_found(t_list *tmp, int i, t_file *file)
{
	char	*str;

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
			return (write(2, "Error\nFile not acceptable\n", 27), 1);
	}
	if (missing_param(file->param))
		return (write(2, "Error\nMissing parameter\n", 25), 1);
	return (0);
}

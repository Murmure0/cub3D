/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:57:09 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/18 10:19:05 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	fill_color(char *str, int *color)
{
	int		i;
	char	**tmp;

	i = parse_spaces(str);
	tmp = ft_split(str + i, ',');
	if (!tmp)
		return (write_ret("Error\nMalloc failed\n"));
	if (trim_spaces(tmp))
		return (1);
	i = arraylen(tmp);
	if (i != 3)
	{
		free_tab(tmp);
		return (write_ret("Error\nWrong nb of colors\n"));
	}
	if (check_color(tmp))
		return (1);
	*color = create_trgb(0, ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
	return (free_tab(tmp), 0);
}

static int	fill_texture(char *str, char **texture)
{
	int	i;

	i = 2;
	i += parse_spaces(str + 2);
	*texture = ft_substr(str, i, ft_strlen(str));
	if (!(*texture))
		return (write_ret("Error\nMalloc failed.\n"));
	if (ft_strncmp(".xpm", &texture[0][ft_strlen(texture[0]) - 4], 4))
		return (write_ret("Error\nWrong texture extension.\n"));
	return (0);
}

static int	param_id_found(t_list *tmp, int i, t_file *file, t_p_nb *p_nb)
{
	char	*line;
	char	*str;

	str = (char *)tmp->content;
	line = tmp->content;
	if (str[i] == 'C')
		return (p_nb->c++, fill_color(++line, &file->param->ceiling));
	else if (str[i] == 'F')
		return (p_nb->f++, fill_color(++line, &file->param->floor));
	else if (str[i] == 'N' && str[i + 1] == 'O')
		return (p_nb->no++, fill_texture(line, &file->param->no));
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (p_nb->so++, fill_texture(line, &file->param->so));
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (p_nb->ea++, fill_texture(line, &file->param->ea));
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (p_nb->we++, fill_texture(line, &file->param->we));
	return (write_ret("Error\nFile not acceptable\n"));
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
	t_p_nb	p_nb;

	param_count_init(&p_nb);
	tmp = file->map;
	while (tmp)
	{
		i = 0;
		i += parse_spaces(tmp->content);
		if (((char *)tmp->content)[i] == '\n')
			tmp = tmp->next;
		else if (map_is_found(file, tmp, i))
			break ;
		else if (!param_id_found(tmp, i, file, &p_nb))
			tmp = tmp->next;
		else
			return (1);
	}
	if (missing_param(p_nb))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche </var/mail/cwastche>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:46:36 by cwastche          #+#    #+#             */
/*   Updated: 2022/04/30 14:46:38 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	spacedstrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			i += 4;
		else
			i++;
	}
	return (i);
}

static int	fill_str_with_spaces(t_file *file, int i, int j)
{
	int	k;

	k = 0;
	while (k < 4)
	{
		file->scene[i][j] = ' ';
		j++;
		k++;
	}
	return (k);
}

static int	fill_scene(t_file *file, t_list *tmp, int i)
{
	int		j;
	char	*str;

	str = tmp->content;
	file->scene[i] = malloc(sizeof(char) * (spacedstrlen(str) + 1));
	if (!file->scene[i])
		return (write(2, "Error\nMalloc failed.\n", 20), 1);
	j = -1;
	while (str[++j])
	{
		if (str[j] == '\t')
			j += fill_str_with_spaces(file, i, j);
		else
			file->scene[i][j] = str[j];
	}
	file->scene[i][j] = 0;
	return (0);
}

static int	check_for_newline(t_list *map)
{
	t_list	*tmp;
	char	*str;
	int		i;

	tmp = map;
	i = 0;
	while (tmp)
	{
		str = tmp->content;
		i = parse_spaces(str);
		if (str[i] == 0 || str[0] == '\n')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	convert_list_to_array(t_file *file)
{
	int		i;
	int		j;
	int		k;
	t_list	*tmp;

	if (check_for_newline(file->map))
		return (write(2, "Error\nEmpty line in map\n", 23), 1);
	i = 0;
	tmp = file->map;
	while (tmp)
	{
		if (fill_scene(file, tmp, i))
			return (1);
		tmp = tmp->next;
		i++;
	}
	file->scene[i] = 0;
	return (0);
}

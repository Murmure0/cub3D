/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:46:36 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/02 12:02:11 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	spacedstrlen(char *str)
{
	int	i;
	int	tab;

	i = -1;
	tab = 0;
	while (str[++i])
	{
		if (str[i] == '\t')
			tab++;
	}
	return (i + tab * 4 - tab);
}

static int	fill_str_with_spaces(t_file *file, int i, int k)
{
	int	j;

	j = 0;
	while (j < 4)
	{
		file->scene[i][k] = ' ';
		j++;
		k++;
	}
	return (j);
}

static int	fill_scene(t_file *file, t_list *tmp, int i)
{
	int		j;
	int		k;
	char	*str;

	str = tmp->content;
	file->scene[i] = malloc(sizeof(char) * (spacedstrlen(str) + 1));
	if (!file->scene[i])
		return (write(2, "Error\nMalloc failed.\n", 20), 1);
	j = -1;
	k = 0;
	while (str[++j])
	{
		if (str[j] == '\t')
			k += fill_str_with_spaces(file, i, k);
		else
		{
			file->scene[i][k] = str[j];
			k++;
		}
	}
	file->scene[i][k] = 0;
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
		if (str[i] == 0 || str[0] == '\n' || str[i] == EOF)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	free_scene(t_file *file, int i)
{
	while (file->scene[--i])
		free(file->scene[i]);
	free(file->scene);
}

int	trim_end_spaces(t_file *file)
{
	int		y;
	int		x;
	int		len;
	char	*tmp;

	y = -1;
	while (file->scene[++y])
	{
		x = 0;
		len = ft_strlen(file->scene[y]);
		while (is_space(file->scene[y][len--]))
			x++;
		tmp = ft_strdup(file->scene[y]);
		free(file->scene[y]);
		file->scene[y] = ft_substr(tmp, 0, ft_strlen(tmp) - x);
		free(tmp);
		if (!file->scene[y])
			return (write(2, "Error\nMalloc failed.\n", 21), 1);
	}
	return (0);
}

int	convert_list_to_array(t_file *file)
{
	int		i;
	t_list	*tmp;

	if (check_for_newline(file->map))
		return (write(2, "Error\nEmpty line in map\n", 23), 1);
	i = 0;
	tmp = file->map;
	file->scene = malloc(sizeof(char *) * (ft_lstsize(file->map) + 1));
	if (!file->scene)
		return (write(2, "Error\nMalloc failed.\n", 21), 1);
	while (tmp)
	{
		if (fill_scene(file, tmp, i))
			return (free_scene(file, i), 1);
		tmp = tmp->next;
		i++;
	}
	file->scene[i] = 0;
	printf("BEFORE\n");
	print_map(file->scene);
	if (trim_end_spaces(file))
		return (1);
	printf("AFTER\n");
	print_map(file->scene);
	return (0);
}

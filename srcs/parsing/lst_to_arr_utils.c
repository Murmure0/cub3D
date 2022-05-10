/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche </var/mail/cwastche>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:28:01 by cwastche          #+#    #+#             */
/*   Updated: 2022/05/10 23:28:03 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		while (is_space(file->scene[y][--len]))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:24:21 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/18 10:25:45 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	dir_params_to_null(t_file *file)
{
	file->param->no = NULL;
	file->param->so = NULL;
	file->param->we = NULL;
	file->param->ea = NULL;
}

int	is_ascii(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] > 127 || str[i] < 0)
			return (0);
	}
	return (1);
}

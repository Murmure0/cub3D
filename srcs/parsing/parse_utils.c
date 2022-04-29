/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:52:10 by cwastche          #+#    #+#             */
/*   Updated: 2022/04/20 11:52:12 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	parse_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 9 || (str[i] >= 11 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

int	missing_param(t_p_nb p_nb)
{
	int	param_count;

	param_count = p_nb.c + p_nb.f + p_nb.ea + p_nb.no + p_nb.so + p_nb.we;
	if (param_count < 6)
		return (write(2, "Error\nMissing parameter\n", 23), 1);
	else if (param_count > 6)
		return (write(2, "Error\nExcess parameters given\n", 29), 1);
	return (0);
}

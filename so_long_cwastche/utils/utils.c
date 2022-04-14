/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:22:12 by cwastche          #+#    #+#             */
/*   Updated: 2022/02/04 09:25:44 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/so_long.h"

void	map_size(t_data *var)
{
	int	y;

	var->map_w = ft_strlen(var->map[0]) * 80;
	var->map_h = 0;
	while (var->map[y++])
		var->map_h += 1;
	var->map_h *= 80;
}

void	map_free(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	error(char *msg, t_data *var)
{
	if (var->map)
		map_free(var->map);
	printf("Error.\n");
	printf("%s\n", msg);
	exit(EXIT_SUCCESS);
}

int	close_win(t_data *var)
{
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	map_free(var->map);
	exit(1);
}

int	error_win(t_data *var, int n)
{
	close_win(var);
	printf("Error.\n");
	if (n == 1)
		printf("Mlx initialization failed.\n");
	if (n == 2)
		printf("Window initialization failed.\n");
	return (1);
}

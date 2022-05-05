/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:40:58 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/09 13:33:12 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_win(t_param *param_mlx)
{
	mlx_destroy_window(param_mlx->mlx_ptr, param_mlx->mlx_win);
	free_pars_map(*param_mlx->map);
	exit(0);
}

int	deal_key(int keycode, t_param *param_mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(param_mlx->mlx_ptr, param_mlx->mlx_win);
		free_pars_map(*param_mlx->map);
		exit(0);
	}
	else if (keycode == 13)
		move_up(param_mlx, param_mlx->map, param_mlx->rabbit, param_mlx->img);
	else if (keycode == 0)
		move_left(param_mlx, param_mlx->map, param_mlx->rabbit, param_mlx->img);
	else if (keycode == 1)
		move_down(param_mlx, param_mlx->map, param_mlx->rabbit, param_mlx->img);
	else if (keycode == 2)
		move_right(param_mlx, param_mlx->map, param_mlx->rabbit,
			param_mlx->img);
	if (param_mlx->map->pars_map[param_mlx->rabbit->y_pos]
		[param_mlx->rabbit->x_pos] == 'E' && param_mlx->map->nb_item == 0)
	{
		mlx_destroy_window(param_mlx->mlx_ptr, param_mlx->mlx_win);
		free_pars_map(*param_mlx->map);
		exit(0);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_r_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:49:40 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/10 11:15:26 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	mv_right_rabbit(t_param *param_mlx, t_img *img,
t_stuff *rabbit, t_map *map)
{
	mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
		img->charac_down, (rabbit->x_pos + 1) * BLOCK_SIZE,
		rabbit->y_pos * BLOCK_SIZE);
	mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
		img->floor, rabbit->x_pos * BLOCK_SIZE, rabbit->y_pos * BLOCK_SIZE);
	rabbit->x_pos++;
	if (map->pars_map[rabbit->y_pos][rabbit->x_pos - 1] == 'E')
		mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
			img->exit, (rabbit->x_pos - 1) * BLOCK_SIZE,
			rabbit->y_pos * BLOCK_SIZE);
}

int	move_right(t_param *param_mlx, t_map *map, t_stuff *rabbit,
t_img *img)
{
	if (map->pars_map[rabbit->y_pos][rabbit->x_pos + 1] != '1')
	{
		if (map->pars_map[rabbit->y_pos][rabbit->x_pos + 1] == 'C')
		{
			map->nb_item--;
			map->pars_map[rabbit->y_pos][rabbit->x_pos + 1] = '0';
		}
		mv_right_rabbit(param_mlx, img, rabbit, map);
		ft_putnbr(param_mlx->z);
		(param_mlx->z)++;
		write(1, "\n", 1);
	}
	return (0);
}

static void	mv_left_rabbit(t_param *param_mlx, t_img *img, t_stuff *rabbit,
t_map *map)
{
	mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
		img->charac_down, (rabbit->x_pos - 1) * BLOCK_SIZE,
		rabbit->y_pos * BLOCK_SIZE);
	mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
		img->floor, rabbit->x_pos * BLOCK_SIZE, rabbit->y_pos * BLOCK_SIZE);
		rabbit->x_pos--;
	if (map->pars_map[rabbit->y_pos][rabbit->x_pos + 1] == 'E')
		mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
			img->exit, (rabbit->x_pos + 1) * BLOCK_SIZE,
			rabbit->y_pos * BLOCK_SIZE);
}

int	move_left(t_param *param_mlx, t_map *map, t_stuff *rabbit,
t_img *img)
{
	if (map->pars_map[rabbit->y_pos][rabbit->x_pos - 1] != '1')
	{
		if (map->pars_map[rabbit->y_pos][rabbit->x_pos - 1] == 'C')
		{
			map->nb_item--;
			map->pars_map[rabbit->y_pos][rabbit->x_pos - 1] = '0';
		}
		mv_left_rabbit(param_mlx, img, rabbit, map);
		ft_putnbr(param_mlx->z);
		(param_mlx->z)++;
		write(1, "\n", 1);
	}
	return (0);
}

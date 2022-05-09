/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_u_d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:46:18 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/10 11:15:34 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	put_counter(t_param *param_mlx, t_map *map, t_img *img)
{
	int	x;

	x = -1;
	while (++x < map->pars_width)
		mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
			img->wall, 0, x * BLOCK_SIZE);
	map->counter = ft_itoa(param_mlx->z);
	if (!map->counter)
	{
		free_pars_map(*map);
		exit(0);
	}
	mlx_string_put(param_mlx->mlx_ptr, param_mlx->mlx_win, 0, 0, 0x00303048,
		map->counter);
	free(map->counter);
	return (1);
}

static void	mv_up_rabbit(t_param *param_mlx, t_img *img, t_stuff *rabbit,
t_map *map)
{
	mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
		img->charac_up, rabbit->x_pos * BLOCK_SIZE,
		(rabbit->y_pos - 1) * BLOCK_SIZE);
	mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
		img->floor, rabbit->x_pos * BLOCK_SIZE, rabbit->y_pos * BLOCK_SIZE);
	rabbit->y_pos--;
	if (map->pars_map[rabbit->y_pos +1][rabbit->x_pos] == 'E')
		mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
			img->exit, rabbit->x_pos * BLOCK_SIZE,
			(rabbit->y_pos + 1) * BLOCK_SIZE);
}

int	move_up(t_param *param_mlx, t_map *map, t_stuff *rabbit, t_img *img)
{
	if (map->pars_map[rabbit->y_pos - 1][rabbit->x_pos] != '1')
	{
		if (map->pars_map[rabbit->y_pos - 1][rabbit->x_pos] == 'C')
		{
			map->nb_item--;
			map->pars_map[rabbit->y_pos - 1][rabbit->x_pos] = '0';
		}
		mv_up_rabbit(param_mlx, img, rabbit, map);
		put_counter(param_mlx, map, img);
		(param_mlx->z)++;
	}
	return (0);
}

static void	mv_down_rabbit(t_param *param_mlx, t_img *img, t_stuff *rabbit,
t_map *map)
{
	mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
		img->charac_down, rabbit->x_pos * BLOCK_SIZE,
		(rabbit->y_pos + 1) * BLOCK_SIZE);
	mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
		img->floor, rabbit->x_pos * BLOCK_SIZE, rabbit->y_pos * BLOCK_SIZE);
		rabbit->y_pos++;
	if (map->pars_map[rabbit->y_pos - 1][rabbit->x_pos] == 'E')
		mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
			img->exit, rabbit->x_pos * BLOCK_SIZE,
			(rabbit->y_pos - 1) * BLOCK_SIZE);
}

int	move_down(t_param *param_mlx, t_map *map, t_stuff *rabbit,
t_img *img)
{
	int	x;

	x = -1;
	if (map->pars_map[rabbit->y_pos + 1][rabbit->x_pos] != '1')
	{
		if (map->pars_map[rabbit->y_pos + 1][rabbit->x_pos] == 'C')
		{
			map->nb_item--;
			map->pars_map[rabbit->y_pos + 1][rabbit->x_pos] = '0';
		}
		mv_down_rabbit(param_mlx, img, rabbit, map);
		put_counter(param_mlx, map, img);
		(param_mlx->z)++;
	}
	return (0);
}

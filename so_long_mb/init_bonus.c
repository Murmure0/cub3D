/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:10:04 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/10 10:53:07 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	initialize_img(t_img *init_img, void *mlx_ptr)
{
	int	img_width;
	int	img_height;

	img_width = 32;
	img_height = 32;
	init_img->item = mlx_xpm_file_to_image(mlx_ptr, "./sprites/carrot.xpm",
			&img_width, &img_height);
	init_img->wall = mlx_xpm_file_to_image(mlx_ptr, "./sprites/wall.xpm",
			&img_width, &img_height);
	init_img->floor = mlx_xpm_file_to_image(mlx_ptr, "./sprites/floor.xpm",
			&img_width, &img_height);
	init_img->charac_up = mlx_xpm_file_to_image(mlx_ptr, "./sprites/up.xpm",
			&img_width, &img_height);
	init_img->charac_down = mlx_xpm_file_to_image(mlx_ptr,
			"./sprites/down.xpm", &img_width, &img_height);
	init_img->charac_right = mlx_xpm_file_to_image(mlx_ptr,
			"./sprites/right.xpm", &img_width, &img_height);
	init_img->charac_left = mlx_xpm_file_to_image(mlx_ptr,
			"./sprites/left.xpm", &img_width, &img_height);
	init_img->exit = mlx_xpm_file_to_image(mlx_ptr, "./sprites/exit.xpm",
			&img_width, &img_height);
	return (0);
}

void	fill_map(t_map map, t_param param_mlx, t_img init_img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map.pars_height)
	{
		x = 0;
		while (x < map.pars_width)
		{	
			if (map.pars_map[y][x] == '1')
				mlx_put_image_to_window(param_mlx.mlx_ptr, param_mlx.mlx_win,
					init_img.wall, x * BLOCK_SIZE, y * BLOCK_SIZE);
			else
				mlx_put_image_to_window(param_mlx.mlx_ptr, param_mlx.mlx_win,
					init_img.floor, x * BLOCK_SIZE, y * BLOCK_SIZE);
			x++;
		}
		y++;
	}
}

static void	put_p(t_param *param_mlx, t_img init_img, int x, int y)
{
	if (param_mlx->put_p == 0)
	{
		mlx_put_image_to_window(param_mlx->mlx_ptr, param_mlx->mlx_win,
			init_img.charac_down, x * BLOCK_SIZE, y * BLOCK_SIZE);
		param_mlx->put_p++;
	}
	else
		param_mlx->map->pars_map[y][x] = '0';
}

void	put_stuff_map(t_map map, t_param param_mlx, t_img init_img)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	param_mlx.put_p = 0;
	while (++y < map.pars_height)
	{
		x = -1;
		while (++x < map.pars_width)
		{
			if (map.pars_map[y][x] == 'C')
			{
				mlx_put_image_to_window(param_mlx.mlx_ptr, param_mlx.mlx_win,
					init_img.item, x * BLOCK_SIZE, y * BLOCK_SIZE);
				param_mlx.map->nb_item++;
			}
			else if (map.pars_map[y][x] == 'E')
				mlx_put_image_to_window(param_mlx.mlx_ptr, param_mlx.mlx_win,
					init_img.exit, x * BLOCK_SIZE, y * BLOCK_SIZE);
			else if (map.pars_map[y][x] == 'P')
				put_p(&param_mlx, init_img, x, y);
		}
	}
}

int	find_rabbit(t_param param_mlx, t_stuff *rabbit)
{
	int	i;
	int	j;

	j = 0;
	while (j < param_mlx.map->pars_height)
	{
		i = 0;
		while (i < param_mlx.map->pars_width)
		{
			if (param_mlx.map->pars_map[j][i] == 'P')
			{
				(*rabbit).x_pos = i;
				(*rabbit).y_pos = j;
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

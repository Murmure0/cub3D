/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:51 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/09 16:16:18 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	init_struct(t_param *param_mlx, t_stuff *rabbit, t_map *map,
t_img *init_img)
{
	param_mlx->mlx_ptr = mlx_init();
	if (!param_mlx->mlx_ptr)
		return (-1);
	param_mlx->z = 1;
	param_mlx->map = map;
	param_mlx->rabbit = rabbit;
	param_mlx->map->nb_item = 0;
	param_mlx->map->counter = "0";
	initialize_img(init_img, param_mlx->mlx_ptr);
	param_mlx->img = init_img;
	return (0);
}

static int	get_map(int argc, char **argv, t_map *map)
{
	map->pars_map = read_map(argc, argv, map);
	if (!map->pars_map)
	{
		write(1, "Error\n", 7);
		return (-1);
	}
	else if (!valid_map(map->pars_map, (*map)))
	{
		write(1, "Error\n", 7);
		free_pars_map(*map);
		return (-1);
	}
	else
		return (0);
}

static void	creat_map(t_param *param_mlx)
{
	fill_map(*param_mlx->map, *param_mlx, *param_mlx->img);
	put_stuff_map(*param_mlx->map, *param_mlx, *param_mlx->img);
	find_rabbit(*param_mlx, param_mlx->rabbit);
	param_mlx->map->pars_map[param_mlx->rabbit->y_pos][param_mlx->rabbit->x_pos]
		= '0';
}

static void	move(t_param *param_mlx)
{
	mlx_hook(param_mlx->mlx_win, 2, 1L << 0, deal_key, param_mlx);
	mlx_hook(param_mlx->mlx_win, 17, 1L << 17, close_win, param_mlx);
	mlx_string_put(param_mlx->mlx_ptr, param_mlx->mlx_win, 0, 0, 0x00303048,
		param_mlx->map->counter);
}

int	main(int argc, char **argv)
{
	t_param	param_mlx;
	t_img	init_img;
	t_stuff	rabbit;
	t_map	map;

	if (init_struct(&param_mlx, &rabbit, &map, &init_img) < 0)
		return (-1);
	if (get_map(argc, argv, &map) < 0)
		return (-1);
	param_mlx.mlx_win = mlx_new_window(param_mlx.mlx_ptr,
			(BLOCK_SIZE * map.pars_width),
			(BLOCK_SIZE * map.pars_height), "R&C");
	if (!param_mlx.mlx_win)
	{
		free_pars_map(map);
		return (-1);
	}
	creat_map(&param_mlx);
	move(&param_mlx);
	mlx_loop(param_mlx.mlx_ptr);
	free_pars_map(map);
	return (0);
}

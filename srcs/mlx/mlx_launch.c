/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:37:44 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/13 17:04:19 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_all(t_mlx *mlx)
{
	if (mlx->init_ptr)
		free(mlx->init_ptr);
	if (mlx->player)
		free(mlx->player);
	if (mlx->ray)
		free(mlx->ray);
	if (mlx->txt)
		free(mlx->txt);
}

int	close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->init_ptr, mlx->win);
	free_all(mlx);
	exit(0);
}

static int	malloc_struct(t_mlx *mlx)
{
	mlx->player = malloc(sizeof(t_player));
	if (!mlx->player)
	{
		write(2, "Error\nMalloc failed\n", 20);
		return (free_all(mlx), 1);
	}
	mlx->ray = malloc(sizeof(t_ray));
	if (!mlx->ray)
	{
		write(2, "Error\nMalloc failed\n", 20);
		return (free_all(mlx), 1);
	}
	mlx->txt = malloc(sizeof(t_txt) * 4);
	if (!mlx->txt)
	{
		write(2, "Error\nMalloc failed\n", 20);
		return (free_all(mlx), 1);
	}
	return (0);
}

int	init_mlx(t_mlx *mlx, t_file *file)
{
	mlx->init_ptr = mlx_init();
	if (!mlx->init_ptr)
	{
		free_all(mlx);
		return (write(2, "Error\nMlx: initialisation failed\n", 33), 1);
	}
	mlx->file = file;
	if (malloc_struct(mlx))
		return (1);
	init_player(mlx, file);
	if (init_texture(mlx, file))
		return (free_all(mlx), 1);
	mlx->win = mlx_new_window(mlx->init_ptr, WIN_W, WIN_H, "Cub3D");
	if (mlx->win == NULL)
	{
		free_all(mlx);
		return (write(2, "Error\nMlx: new window init. failed.\n", 36), 1);
	}
	return (0);
}

int	launch_mlx(t_mlx *mlx, t_file *file)
{
	if (init_mlx(mlx, file))
		return (1);
	creat_image(mlx, file);
	mlx_hook(mlx->win, 2, 1L << 0, deal_press_key, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, deal_release_key, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_win, mlx);
	mlx_loop_hook(mlx->init_ptr, render_next_frame, mlx);
	return (0);
}

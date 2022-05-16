/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:37:44 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/16 15:49:40 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_all(t_mlx *mlx)
{
	free_tab(mlx->file->scene);
	free(mlx->file->param->no);
	free(mlx->file->param->ea);
	free(mlx->file->param->so);
	free(mlx->file->param->we);
	free(mlx->init_ptr);
	free(mlx->player);
	free(mlx->ray);
	free(mlx->txt);
}

int	close_win(t_mlx *mlx)
{
	mlx_destroy_image(mlx->init_ptr, mlx->img);
	mlx_destroy_window(mlx->init_ptr, mlx->win);
	free_all(mlx);
	exit(0);
}

static int	malloc_struct(t_mlx *mlx)
{
	mlx->player = malloc(sizeof(t_player));
	mlx->ray = malloc(sizeof(t_ray));
	mlx->txt = malloc(sizeof(t_txt) * 4);
	if (!mlx->player || !mlx->ray || !mlx->txt)
	{
		write(2, "Error\nMalloc failed\n", 20);
		return (free_all(mlx), 1);
	}
	return (0);
}

int	init_mlx(t_mlx *mlx, t_file *file)
{
	mlx->file = file;
	mlx->player = NULL;
	mlx->ray = NULL;
	mlx->txt = NULL;
	mlx->win = NULL;
	mlx->init_ptr = mlx_init();
	if (!mlx->init_ptr)
	{
		free_all(mlx);
		return (write(2, "Error\nMlx: initialisation failed\n", 33), 1);
	}
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
	if (creat_image(mlx, file))
		return (1);
	mlx_hook(mlx->win, 2, 1L << 0, deal_press_key, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, deal_release_key, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_win, mlx);
	mlx_loop_hook(mlx->init_ptr, render_next_frame, mlx);
	return (0);
}

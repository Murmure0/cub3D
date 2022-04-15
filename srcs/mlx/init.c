/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:37:44 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/14 18:07:25 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->init_ptr, mlx->win);
	free(mlx->init_ptr);
	//free ce qui a ete parse : map & info
	exit(0);
}

/*keys : W,A,S,D && left & righ*/
int	deal_key(int keycode, t_mlx *mlx, t_file *file)
{
	(void)file;
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->init_ptr, mlx->win);
		//free ce qui a ete parse : map & info
		exit(0);
	}
	// else if (keycode == 13)
	// 	move_up(mlx, file);
	// else if (keycode == 0)
	// 	move_left(mlx, file);
	// else if (keycode == 1)
	// 	move_down(mlx, file);
	// else if (keycode == 2)
	// 	move_right(mlx, file);
	// else if (keycode == 123)
	// 	turn_left(mlx, file);
	// else if (keycode == 124)
	// 	turn_right(mlx, file);
	return (0);
}

// void init_img(t_file)
// {

// }

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr_img + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void put_ceiling_floor(t_mlx *mlx, t_file *file)
{

}

int init_mlx(t_mlx *mlx, t_file *file)
{
	(void)file;
	mlx->init_ptr = mlx_init();
	if(!mlx->init_ptr)
		return (write(2, "Error\nMlx: initialisation failed.\n", 33), 1);
	mlx->win = mlx_new_window(mlx->init_ptr, 1920, 1080, "Cub3D");
	if (mlx->win == NULL)
			return (write(2, "Error\nMlx: new window init. failed.\n", 36), 1);

	put_ceiling_floor(mlx, file);
	mlx->img = mlx_new_image(mlx->init_ptr, 1920, 1080);

	mlx->addr_img = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);

	my_mlx_pixel_put(mlx, 0, 0, 0x00FF0000);
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
	mlx_hook(mlx->win, 2, 1L << 0, deal_key, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_win, mlx);
	return (0);
}

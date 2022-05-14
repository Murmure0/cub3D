/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_new_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:44:30 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/13 16:53:54 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr_img + (y * mlx->line_length
			+ x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// Print player on minimap
static void	gen_mini_player(t_mlx *mlx, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -2;
		while (j++ < 1)
		{
			my_mlx_pixel_put(mlx, (player->dx_pos) * SCALE_MAP - 1 + i,
				(player->dy_pos) * SCALE_MAP + j, 0xB22222);
		}
	}
}

// Print minimap
static void	print_minimap_square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = x * SCALE_MAP;
	while (i < (x + 1) * SCALE_MAP)
	{
		j = y * SCALE_MAP;
		while (j < (y + 1) * SCALE_MAP)
		{
			if (i % SCALE_MAP == 0 || j % SCALE_MAP == 0)
				my_mlx_pixel_put(mlx, i, j, 0xAACCCCCC);
			else
				my_mlx_pixel_put(mlx, i, j, color);
			j++;
		}
		i++;
	}
}

void	creat_game_image(t_mlx *mlx, t_file *file)
{
	int	x;
	int	y;

	put_first_ray(file, mlx, mlx->player, mlx->ray);
	y = -1;
	while (file->scene[++y])
	{
		x = -1;
		while (file->scene[y][++x])
		{
			if (file->scene[y][x] == '1')
				print_minimap_square(mlx, x, y, 0x00000000);
			else if (file->scene[y][x] == '0' || file->scene[y][x] == 'N' ||
					file->scene[y][x] == 'E' || file->scene[y][x] == 'W' ||
					file->scene[y][x] == 'S')
				print_minimap_square(mlx, x, y, 0x00FFFFFF);
		}
	}
	gen_mini_player(mlx, mlx->player);
}

void	creat_image(t_mlx *mlx, t_file *file)
{
	mlx->img = mlx_new_image(mlx->init_ptr, WIN_W, WIN_H);
	mlx->addr_img = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	creat_game_image(mlx, file);
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
}

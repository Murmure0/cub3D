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
static void	gen_mini_player(t_mlx *mlx, t_player *player, double x_offset, double y_offset)
{
	int	i;
	int	j;

	(void)y_offset;
	(void)x_offset;
	

	printf("%f\n",(player->dx_pos - x_offset));
	i = -1;
	while (++i < 3)
	{
		j = -2;
		while (j++ < 1)
		{
			my_mlx_pixel_put(mlx, ((player->dx_pos - x_offset) * SCALE_MAP - 1 + i),
				((player->dy_pos - y_offset) * SCALE_MAP + j), 0xB22222);
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

double	minimap_offset(double player_axis_coord, int window)
{
	double	ret;

	ret = 0;
	while ((player_axis_coord + 1.0 - ret) >= (window / 3 / 16))
		ret += 0.05;
	return (ret);
}

void	creat_game_image(t_mlx *mlx, t_file *file)
{
	int	x;
	int	y;
	double	width_offset;
	double	height_offset;

	put_first_ray(file, mlx, mlx->player, mlx->ray);
	width_offset = minimap_offset(mlx->player->dx_pos, WIN_W);
	height_offset = minimap_offset(mlx->player->dy_pos, WIN_H);
	y = height_offset;
	while (file->scene[y] && y < (WIN_H / 3 / 16) + height_offset)
	{
		x = width_offset;
		while (file->scene[y][x] && x < (WIN_W / 3 / 16) + width_offset)
		{
			if (file->scene[y][x] == '1')
				print_minimap_square(mlx, x - width_offset, y - height_offset, 0x00000000);
			else if (file->scene[y][x] == '0' || file->scene[y][x] == 'N' ||
					file->scene[y][x] == 'E' || file->scene[y][x] == 'W' ||
					file->scene[y][x] == 'S')
				print_minimap_square(mlx, x - width_offset, y - height_offset, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	gen_mini_player(mlx, mlx->player, width_offset, height_offset);
}

void	creat_image(t_mlx *mlx, t_file *file)
{
	mlx->img = mlx_new_image(mlx->init_ptr, WIN_W, WIN_H);
	mlx->addr_img = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	creat_game_image(mlx, file);
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
}

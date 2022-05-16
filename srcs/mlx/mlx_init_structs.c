/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:36:30 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/16 16:13:26 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_dir_player(t_mlx *mlx, t_file *file, int x, int y)
{
	if (file->scene[y][x] == 'N')
		mlx->player->player_dir = M_PI_2;
	else if (file->scene[y][x] == 'E')
		mlx->player->player_dir = 0;
	else if (file->scene[y][x] == 'W')
		mlx->player->player_dir = M_PI;
	else if (file->scene[y][x] == 'S')
		mlx->player->player_dir = 3 * M_PI_2;
}

static void	init_push_button(t_mlx *mlx)
{
	mlx->player->up_press = 0;
	mlx->player->down_press = 0;
	mlx->player->right_press = 0;
	mlx->player->left_press = 0;
	mlx->player->rot_l_press = 0;
	mlx->player->rot_r_press = 0;
}

void	init_player(t_mlx *mlx, t_file *file)
{
	int	x;
	int	y;

	y = -1;
	while (file->scene[++y])
	{
		x = -1;
		while (file->scene[y][++x])
		{
			if (file->scene[y][x] == 'N' || file->scene[y][x] == 'E' ||
			file->scene[y][x] == 'W' || file->scene[y][x] == 'S')
			{
				mlx->player->x_pos = x;
				mlx->player->dx_pos = (double)x + 0.5;
				mlx->player->y_pos = y;
				mlx->player->dy_pos = (double)y + 0.5;
				init_dir_player(mlx, file, x, y);
			}
		}
	}
	init_push_button(mlx);
}

static int	init_texture_ptr_adr(t_mlx *mlx, char *filename, int orientation)
{
	mlx->txt[orientation].txt_ptr = mlx_xpm_file_to_image(mlx->init_ptr,
			filename, &mlx->txt[orientation].w, &mlx->txt[orientation].h);
	if (!mlx->txt[orientation].txt_ptr)
		return (write(2, "Error\nWrong texture path\n", 25), 1);
	mlx->txt[orientation].txt_adr = mlx_get_data_addr(
			mlx->txt[orientation].txt_ptr, &mlx->txt[orientation].bpp,
			&mlx->txt[orientation].len, &mlx->txt[orientation].endian);
	if (!mlx->txt[orientation].txt_adr)
		return (write(2, "Error\nmlx_get_data_addr failed\n", 31), 1);
	return (0);
}

int	init_texture(t_mlx *mlx, t_file *file)
{
	if (init_texture_ptr_adr(mlx, file->param->we, WEST))
		return (1);
	else if (init_texture_ptr_adr(mlx, file->param->no, NORTH))
		return (1);
	else if (init_texture_ptr_adr(mlx, file->param->ea, EAST))
		return (1);
	else if (init_texture_ptr_adr(mlx, file->param->so, SOUTH))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:32:20 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/13 17:03:00 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	wall_collision(t_mlx *mlx, double px, double py)
{
	char	**map;

	map = mlx->file->scene;
	if (map[(int)(py + 4 * SPEED)][(int)px] == '1')
		return (1);
	if (map[(int)py][(int)(px - 4 * SPEED)] == '1')
		return (1);
	if (map[(int)(py - 4 * SPEED)][(int)px] == '1')
		return (1);
	if (map[(int)py][(int)(px + 4 * SPEED)] == '1')
		return (1);
	return (0);
}

void	press_move_up(t_mlx *mlx)
{
	double	dir_y;
	double	dir_x;
	double	new_dx_pos;
	double	new_dy_pos;

	dir_x = cos(mlx->player->player_dir);
	dir_y = sin(mlx->player->player_dir);
	new_dx_pos = mlx->player->dx_pos + dir_x * SPEED;
	new_dy_pos = mlx->player->dy_pos + dir_y * SPEED;
	if (!wall_collision(mlx, new_dx_pos, new_dy_pos))
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

void	press_move_down(t_mlx *mlx)
{
	double	dir_y;
	double	dir_x;
	double	new_dx_pos;
	double	new_dy_pos;

	dir_x = cos(mlx->player->player_dir);
	dir_y = sin(mlx->player->player_dir);
	new_dx_pos = mlx->player->dx_pos - dir_x * SPEED;
	new_dy_pos = mlx->player->dy_pos - dir_y * SPEED;
	if (!wall_collision(mlx, new_dx_pos, new_dy_pos))
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

void	press_move_left(t_mlx *mlx)
{
	double	dir_y;
	double	dir_x;
	double	new_dx_pos;
	double	new_dy_pos;

	dir_x = cos(mlx->player->player_dir + (M_PI_2));
	dir_y = sin(mlx->player->player_dir - (M_PI_2));
	new_dx_pos = mlx->player->dx_pos - dir_x * SPEED;
	new_dy_pos = mlx->player->dy_pos + dir_y * SPEED;
	if (!wall_collision(mlx, new_dx_pos, new_dy_pos))
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

void	press_move_right(t_mlx *mlx)
{
	double	dir_y;
	double	dir_x;
	double	new_dx_pos;
	double	new_dy_pos;

	dir_x = cos(mlx->player->player_dir - (M_PI_2));
	dir_y = sin(mlx->player->player_dir + (M_PI_2));
	new_dx_pos = mlx->player->dx_pos - dir_x * SPEED;
	new_dy_pos = mlx->player->dy_pos + dir_y * SPEED;
	if (!wall_collision(mlx, new_dx_pos, new_dy_pos))
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

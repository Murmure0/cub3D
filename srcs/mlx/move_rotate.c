/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:31:14 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/13 16:38:59 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	press_turn_left(t_mlx *mlx)
{
	mlx->player->player_dir -= SPEED;
	if (mlx->player->player_dir < 0)
		mlx->player->player_dir += 2 * M_PI;
}

void	press_turn_right(t_mlx *mlx)
{
	mlx->player->player_dir += SPEED;
	if (mlx->player->player_dir > 2 * M_PI)
		mlx->player->player_dir -= 2 * M_PI;
}

int	deal_press_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->init_ptr, mlx->win);
		free_all(mlx);
		exit(0);
	}
	else if (keycode == 13)
		mlx->player->up_press = 1;
	else if (keycode == 0)
		mlx->player->left_press = 1;
	else if (keycode == 1)
		mlx->player->down_press = 1;
	else if (keycode == 2)
		mlx->player->right_press = 1;
	else if (keycode == 123)
		mlx->player->rot_l_press = 1;
	else if (keycode == 124)
		mlx->player->rot_r_press = 1;
	return (0);
}

int	deal_release_key(int keycode, t_mlx *mlx)
{
	if (keycode == 13)
		mlx->player->up_press = 0;
	else if (keycode == 0)
		mlx->player->left_press = 0;
	else if (keycode == 1)
		mlx->player->down_press = 0;
	else if (keycode == 2)
		mlx->player->right_press = 0;
	else if (keycode == 123)
		mlx->player->rot_l_press = 0;
	else if (keycode == 124)
		mlx->player->rot_r_press = 0;
	return (0);
}

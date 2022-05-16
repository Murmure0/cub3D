/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_nxt_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:27:16 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/16 15:18:15 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	update_player_pos(t_mlx *mlx)
{
	if (mlx->player->up_press == 1)
		press_move_up(mlx);
	else if (mlx->player->down_press == 1)
		press_move_down(mlx);
	if (mlx->player->left_press == 1)
		press_move_left(mlx);
	else if (mlx->player->right_press == 1)
		press_move_right(mlx);
	if (mlx->player->rot_l_press == 1)
		press_turn_left(mlx);
	else if (mlx->player->rot_r_press == 1)
		press_turn_right(mlx);
}

// When specific event occurs: calculate && put to window new img
int	render_next_frame(void *mlxb)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlxb;
	update_player_pos(mlx);
	creat_game_image(mlx, mlx->file);
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
	//mlx_destroy_img(mlx_ptr, mlx_img)
	return (0);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr_img + (y * mlx->line_length
			+ x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

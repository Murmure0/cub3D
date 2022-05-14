/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_nxt_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:27:16 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/13 17:03:42 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	update_player_pos(t_mlx *mlx)
{
	if (mlx->player->up_press == 1)
		press_move_up(mlx);
	if (mlx->player->down_press == 1)
		press_move_down(mlx);
	if (mlx->player->left_press == 1)
		press_move_left(mlx);
	if (mlx->player->right_press == 1)
		press_move_right(mlx);
	if (mlx->player->rot_l_press == 1)
		press_turn_left(mlx);
	if (mlx->player->rot_r_press == 1)
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
	return (0);
}

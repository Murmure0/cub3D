/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:32:20 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/21 17:37:23 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_up(t_mlx *mlx)
{
	//if (mlx->file->scene[mlx->player->y_pos - 1][mlx->player->x_pos] != '1')
	{
		my_mlx_pixel_put(mlx, mlx->player->x_pos, mlx->player->y_pos - 1, 0xB22222);
		mlx->player->y_pos--;
	}
}

/*keys : W,A,S,D && left & righ : WIP
creation  de fonctions qui reactualiseront la position du perso + les images a l'ecran qd une touche est appuyee*/
int	deal_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		//mlx_destroy_image(mlx->init_ptr, mlx->img);
		mlx_destroy_window(mlx->init_ptr, mlx->win);
		free_all(mlx->file, mlx);
		exit(0);
	}
	// else if (keycode == 13)
	// {
	// 	move_up(mlx);
	// 	printf("contenu de la tile du dessus : %c", mlx->file->scene[mlx->player->y_pos - 1][mlx->player->x_pos]);
	// }
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

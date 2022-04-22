/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:32:20 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/22 14:09:25 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
Deplacement sur la minimap en fractionnant les carrés (de 16x16pxl) par SPEED = 0.05

Deux positions pour le joueur : 
- une en int pour le tableau (y_pos/x_pos) mlx->file->scene[y][x]
- une en double (dy_pos/dx_pos) pour se deplacer dans le carré de la minimap : sinon on saute de carré en carré
Le cast en int donne toujours un arrondis vers le bas & permet de passer les valeurs dans le tableau

Rappel : x/y à 0/0 en haut a gauche de la fenetre
Axe x : droite : + valeur // gauche : - valeur
Axe y : descendre : + valeur // monter : - valeur 
*/

void	press_move_up(t_mlx *mlx)
{
	if (mlx->file->scene[(int)(mlx->player->dy_pos - SPEED)][(int)(mlx->player->dx_pos)] != '1')
	{
		mlx->player->up_press = 1;
		mlx->player->dy_pos -= SPEED;
		mlx->player->y_pos = (int)mlx->player->dy_pos;
	}
}

void	press_move_down(t_mlx *mlx)
{
	if (mlx->file->scene[(int)(mlx->player->dy_pos + SPEED)][(int)(mlx->player->dx_pos)] != '1')
	{
		mlx->player->up_press = 1;
		mlx->player->dy_pos += SPEED;
		mlx->player->y_pos = (int)mlx->player->dy_pos;
	}
}

void	press_move_left(t_mlx *mlx)
{
	if (mlx->file->scene[(int)(mlx->player->dy_pos)][(int)(mlx->player->dx_pos - SPEED)] != '1')
	{
		mlx->player->up_press = 1;
		mlx->player->dx_pos -= SPEED;
		mlx->player->x_pos = (int)mlx->player->dx_pos;
	}
}

void	press_move_right(t_mlx *mlx)
{
	if (mlx->file->scene[(int)(mlx->player->dy_pos)][(int)(mlx->player->dx_pos + SPEED)] != '1')
	{
		mlx->player->up_press = 1;
		mlx->player->dx_pos += SPEED;
		mlx->player->x_pos = (int)mlx->player->dx_pos;
	}
}

/*WIP : trouver comment prendre en compte l'angle de vu et comment tourner*/
int	deal_press_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->init_ptr, mlx->win);
		free_all(mlx->file, mlx);
		exit(0);
	}
	else if (keycode == 13)
		press_move_up(mlx);
	else if (keycode == 0)
		press_move_left(mlx);
	else if (keycode == 1)
		press_move_down(mlx);
	else if (keycode == 2)
		press_move_right(mlx);
	// else if (keycode == 123)
	// 	press_turn_left(mlx, file);
	// else if (keycode == 124)
	// 	press_turn_right(mlx, file);
	return (0);
}

/*
Actualise la variable mlx->player->(direction)_press, qui indique si on est en train de presser une touche : 
au moment de relacher la touche la variable est remise a 0,
elle passe à 1 dans la fonction deal_press_key lorsque la touche est pressée

WIP : va permettre d'evaluer le temps où la touche a ete pressée pour des calculs futurs de distance/d'angle parcouru
*/
int	deal_release_key(int keycode, t_mlx *mlx)
{
	(void)mlx;

	if (keycode == 13)
		mlx->player->up_press = 0;
	else if (keycode == 0)
		mlx->player->left_press = 0;
	else if (keycode == 1)
		mlx->player->down_press = 0;
	else if (keycode == 2)
		mlx->player->right_press = 0;
	// else if (keycode == 123)
	// 	release_turn_left(mlx, file);
	// else if (keycode == 124)
	// 	release_turn_right(mlx, file);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:32:20 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/12 09:28:40 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
Les move seront a modifier en fonction de la direction vers lequel le player regarde

Deplacement sur la minimap en fractionnant les carrés (de 16x16pxl) par SPEED = 0.05

Deux positions pour le joueur : 
- une en int pour le tableau (y_pos/x_pos) mlx->file->scene[y][x]
- une en double (dy_pos/dx_pos) pour se deplacer dans le carré de la minimap : sinon on saute de carré en carré
Le cast en int donne toujours un arrondis vers le bas & permet de passer les valeurs dans le tableau

Rappel :
 x/y à 0/0 en haut a gauche de la fenetre
Axe x /cos : droite (est): + valeur // gauche (ouest): - valeur
Axe y /sin: descendre (sud): + valeur // monter (nord): - valeur 
*/
void	press_move_up(t_mlx *mlx)
{

	double	dirY;
	double	dirX;
	double	new_dx_pos;
	double	new_dy_pos;

	dirX = cos(mlx->player->player_dir);
	dirY = sin(mlx->player->player_dir);
	new_dx_pos = mlx->player->dx_pos + dirX * SPEED;
	new_dy_pos = mlx->player->dy_pos + dirY * SPEED;

	if (mlx->file->scene[(int)(new_dy_pos - 2*SPEED)][(int)(new_dx_pos + 2*SPEED)] != '1')
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

void	press_move_down(t_mlx *mlx)
{
	double	dirY;
	double	dirX;
	double	new_dx_pos;
	double	new_dy_pos;

	dirX = cos(mlx->player->player_dir);
	dirY = sin(mlx->player->player_dir);
	new_dx_pos = mlx->player->dx_pos - dirX * SPEED;
	new_dy_pos = mlx->player->dy_pos - dirY * SPEED;
	if (mlx->file->scene[(int)(new_dy_pos + 2*SPEED)][(int)(new_dx_pos + 2*SPEED)] != '1')
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

void	press_move_left(t_mlx *mlx)
{
	double	dirY;
	double	dirX;
	double	new_dx_pos;
	double	new_dy_pos;

	dirX = cos(mlx->player->player_dir + (M_PI/2));
	dirY = sin(mlx->player->player_dir - (M_PI/2));
	new_dx_pos = mlx->player->dx_pos + dirX * SPEED;
	new_dy_pos = mlx->player->dy_pos + dirY * SPEED;
	if (mlx->file->scene[(int)(new_dy_pos + 2*SPEED)][(int)(new_dx_pos - 2*SPEED)] != '1')
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

void	press_move_right(t_mlx *mlx)
{
	double	dirY;
	double	dirX;
	double	new_dx_pos;
	double	new_dy_pos;

	dirX = cos(mlx->player->player_dir - (M_PI/2)) ;
	dirY = sin(mlx->player->player_dir + (M_PI/2)) ;
	new_dx_pos = mlx->player->dx_pos + dirX * SPEED;
	new_dy_pos = mlx->player->dy_pos + dirY * SPEED;
	if (mlx->file->scene[(int)(new_dy_pos + 2*SPEED)][(int)(new_dx_pos + 2*SPEED)] != '1')
	{
		mlx->player->dx_pos = new_dx_pos;
		mlx->player->dy_pos = new_dy_pos;
	}
}

void	press_turn_left(t_mlx *mlx)
{
	mlx->player->player_dir -= SPEED;
	if (mlx->player->player_dir < 0) // on reinitialise la position apres un tour complet
		mlx->player->player_dir += 2 * M_PI;
}

void	press_turn_right(t_mlx *mlx)
{
	mlx->player->player_dir += SPEED;
	if (mlx->player->player_dir > 2 * M_PI) //idem
		mlx->player->player_dir -= 2 * M_PI;
}

/*WIP : trouver comment prendre en compte l'appuyage de la touche pour que ce soit plus smooth dans les deplacements*/
int	deal_press_key(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->init_ptr, mlx->win);
		free_all(mlx->file, mlx);
		//system("leaks cub3d");
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
	(void)mlx;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:32:20 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/06 09:55:40 by mberthet         ###   ########.fr       */
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

int	dir_of_mvmt_up(t_mlx *mlx, double new_dx_pos, double new_dy_pos, double dirX, double dirY)
{

	(void)mlx;
	(void)new_dx_pos;
	(void)new_dy_pos;
	//Les coins ne sont pas repris dans cette decoupe
	printf("X: %f Y: %f\n", dirX, dirY);
	if (dirX >= -0.5 && dirX < 0.5 && dirY <= 1.0 && dirY >= 0.5)
		printf("NORTH\n");
	else if (dirX >= -0.5 && dirX < 0.5 && dirY >= -1.0 && dirY <= -0.5)
		printf("SOUTH\n");
	else if (dirX >= -1.0 && dirX <= -0.5 && dirY >= -0.5 && dirY <= 0.5)
		printf("WEST\n");
	else if (dirX <= 1.0 && dirX >= 0.5 && dirY >= -0.5 && dirY <= 0.5)
		printf("EAST\n");
	else if (dirX > 0.5 && dirY > 0.5 && dirY < 0.75)
		printf("Left (EAST)\n");
	else if ((dirX > 0.5 && dirY > 0.75) || (dirX < -0.5 && dirX > -0.75 && dirY > 0.5))
		printf("UP - north\n");
	else if (dirX < -0.75 && dirY > 0.5)
		printf("east\n"); // to work on condition
	else if (dirX < -0.5 && dirY < -0.5)
		printf("West \n"); // to work on condition
	else if (dirX > 0.5 && dirY < -0.5)
		printf("SOUTH\n")
	return (0);
}

//invert north and south, east and west
int	dir_of_mvmt_down(t_mlx *mlx, double new_dx_pos, double new_dy_pos, double dirX, double dirY)
{

	(void)mlx;
	(void)new_dx_pos;
	(void)new_dy_pos;
	//Les coins ne sont pas repris dans cette decoupe
	printf("X: %f Y: %f\n", dirX, dirY);
	if (dirX >= -0.5 && dirX < 0.5 && dirY <= 1.0 && dirY >= 0.5)
		printf("SOUTH\n");
	else if (dirX >= -0.5 && dirX < 0.5 && dirY >= -1.0 && dirY <= -0.5)
		printf("NORTH\n");
	else if (dirX >= -1.0 && dirX <= -0.5 && dirY >= -0.5 && dirY <= 0.5)
		printf("EAST\n");
	else if (dirX <= 1.0 && dirX >= 0.5 && dirY >= -0.5 && dirY <= 0.5)
		printf("WEST\n");
	return (0);
}


//Orientation decale un quart de tour dans le sens contraire des aiguilles d'une horloge
int	dir_of_mvmt_left(t_mlx *mlx, double new_dx_pos, double new_dy_pos, double dirX, double dirY)
{

	(void)mlx;
	(void)new_dx_pos;
	(void)new_dy_pos;
	//Les coins ne sont pas repris dans cette decoupe
	printf("X: %f Y: %f\n", dirX, dirY);
	if (dirX >= -0.5 && dirX < 0.5 && dirY <= 1.0 && dirY >= 0.5)
		printf("WEST\n");
	else if (dirX >= -0.5 && dirX < 0.5 && dirY >= -1.0 && dirY <= -0.5)
		printf("EAST\n");
	else if (dirX >= -1.0 && dirX <= -0.5 && dirY >= -0.5 && dirY <= 0.5)
		printf("SOUTH\n");
	else if (dirX <= 1.0 && dirX >= 0.5 && dirY >= -0.5 && dirY <= 0.5)
		printf("NORTH\n");
	return (0);
}

//Orientation decale un quart de tour dans le sens des aiguilles d'une horloge
int	dir_of_mvmt_right(t_mlx *mlx, double new_dx_pos, double new_dy_pos, double dirX, double dirY)
{

	(void)mlx;
	(void)new_dx_pos;
	(void)new_dy_pos;
	//Les coins ne sont pas repris dans cette decoupe
	printf("X: %f Y: %f\n", dirX, dirY);
	if (dirX >= -0.5 && dirX < 0.5 && dirY <= 1.0 && dirY >= 0.5)
		printf("EAST\n");
	else if (dirX >= -0.5 && dirX < 0.5 && dirY >= -1.0 && dirY <= -0.5)
		printf("WEST\n");
	else if (dirX >= -1.0 && dirX <= -0.5 && dirY >= -0.5 && dirY <= 0.5)
		printf("NORTH\n");
	else if (dirX <= 1.0 && dirX >= 0.5 && dirY >= -0.5 && dirY <= 0.5)
		printf("SOUTH\n");
	return (0);
}

void	press_move_up(t_mlx *mlx)
{

	double	dirY;
	double	dirX;
	double	new_dx_pos;
	double	new_dy_pos;

	// double dmap_h = mlx->file->map_h - 1.0;
	// double dmap_w = mlx->file->map_w - 1.0; 

	dirX = cos(mlx->player->player_dir);
	dirY = sin(mlx->player->player_dir);
	new_dx_pos = mlx->player->dx_pos + dirX * SPEED;
	new_dy_pos = mlx->player->dy_pos + dirY * SPEED;

	dir_of_mvmt_up(mlx, new_dx_pos, new_dy_pos, dirX, dirY);

	if (mlx->file->scene[(int)(new_dy_pos - 2*SPEED)][(int)(new_dx_pos + 2*SPEED)] != '1') //&& (int)(new_dy_pos - 2*SPEED) < dmap_h && (int)(new_dx_pos + 2*SPEED) < dmap_w && (int)(new_dy_pos - 2*SPEED) > 0 && (int)(new_dx_pos + 2*SPEED) > 0
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

	dir_of_mvmt_down(mlx, new_dx_pos, new_dy_pos, dirX, dirY);

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

	dir_of_mvmt_left(mlx, new_dx_pos, new_dy_pos, cos(mlx->player->player_dir), sin(mlx->player->player_dir));
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

	dir_of_mvmt_right(mlx, new_dx_pos, new_dy_pos, cos(mlx->player->player_dir), sin(mlx->player->player_dir));
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

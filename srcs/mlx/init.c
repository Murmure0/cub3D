/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:37:44 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/09 13:43:59 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*WIP : ajouter ici tout ce qui doit etre free avant de quitter le programme*/
void free_all(t_file *file, t_mlx *mlx)
{
	(void)file;

	if (mlx->init_ptr)
		free(mlx->init_ptr);
	if (mlx->player)
		free(mlx->player);
	// if(mlx->win)
	// 	free(mlx->win); //NE PAS FREE : double free avec mlx_destroy_window
	if (mlx->ray)
		free(mlx->ray);
}

int	close_win(t_mlx *mlx, t_file *file)
{
	(void)file;

	mlx_destroy_window(mlx->init_ptr, mlx->win);
	free_all(file, mlx);
	//system("leaks cub3d");
	exit(0);
}

/*Initialise la direction du player en fontion de la lettre N/S/E/W*/
void	init_dir_player(t_mlx *mlx, t_file *file, int x, int y)
{
	if (file->scene[y][x] == 'N')
		mlx->player->player_dir = M_PI/2;
	else if(file->scene[y][x] == 'E')
		mlx->player->player_dir = 0;
	else if(file->scene[y][x] == 'W')
		mlx->player->player_dir = M_PI;
	else if(file->scene[y][x] == 'S')
		mlx->player->player_dir = 3 * M_PI/2;
}

void	init_push_button(t_mlx *mlx)
{
	mlx->player->up_press = 0;
	mlx->player->down_press = 0;
	mlx->player->right_press = 0;
	mlx->player->left_press = 0;
	mlx->player->rot_l_press = 0;
	mlx->player->rot_r_press = 0;
}

/*Initialise la position du player dans sa structure*/
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
				mlx->player->x_pos = x ;
				mlx->player->dx_pos = (double)x + 0.5;
				mlx->player->y_pos = y;
				mlx->player->dy_pos = (double)y + 0.5;
				init_dir_player(mlx, file, x, y);
			}
		}
	}
	init_push_button(mlx);
}

/*initialise les textures dans le tab de textures*/
int	init_texture_ptr_adr(t_mlx *mlx, char *filename, int orientation)
{
	mlx->txt[orientation].txt_ptr = mlx_xpm_file_to_image(mlx->init_ptr, filename, &mlx->txt[orientation].w, &mlx->txt[orientation].h);
	if(!mlx->txt[orientation].txt_ptr)
		return(1);
	mlx->txt[orientation].txt_adr = mlx_get_data_addr(&mlx->init_ptr, &mlx->txt[orientation].bpp, &mlx->txt[orientation].len, &mlx->txt[orientation].endian);
	return (0);
}

int	init_texture(t_mlx *mlx, t_file *file)
{
	if (init_texture_ptr_adr(mlx, file->param->ea, EST))
		return(1);
	if (init_texture_ptr_adr(mlx, file->param->no, NORTH))
		return(1);
	if (init_texture_ptr_adr(mlx, file->param->we, WEST))
		return(1);
	if (init_texture_ptr_adr(mlx, file->param->so, SOUTH))
		return(1);
	return (0);
}

/*
Initialisation du pointeur mlx, de la fenetre, des xpm, de la position du player
et des param de la camera (voir camera.c)
*/
int init_mlx(t_mlx *mlx, t_file *file)
{
	mlx->player = malloc(sizeof(t_player));
	if (!mlx->player)
	{
		free_all(file, mlx);
		return (1);
	}
	mlx->init_ptr = mlx_init();
	if(!mlx->init_ptr)
	{
		free_all(file, mlx);
		return (write(2, "Error\nMlx: initialisation failed.\n", 33), 1);
	}
	mlx->win = mlx_new_window(mlx->init_ptr, WIN_W, WIN_H, "Cub3D");
	if (mlx->win == NULL)
	{
		free_all(file, mlx);
		return (write(2, "Error\nMlx: new window init. failed.\n", 36), 1);
	}
	mlx->ray = malloc(sizeof(t_ray));
	if (!mlx->ray)
	{
		free_all(file, mlx);
		return (write(2, "Error\nInit. ray failed.\n", 36), 1);
	}
	mlx->txt = malloc(sizeof(t_txt) * 4);
	if (!mlx->txt)
	{
		free_all(file, mlx);
		return(1);
	}
	init_player(mlx, file); //verif les retours
	if (init_texture(mlx, file))
		return (1);
	mlx->file = file;
	return (0);
}

/*Lancement de la mlx :
Initialisation des parametres issus de la map

mlx_hook permet de reperer lorsqu'un event arrive :
- "2, 1L << 0" qd on appuit sur une touche
- "3, 1L << 1" qd on relache une touche
- "17, 1L << 17" qd on clique sur la croix rouge pour detruire la fenetre

mlx_loop_hook permet d'actualiser l'image en temps reel en fonction des events qui ont eu lieu
*/
int launch_mlx(t_mlx *mlx, t_file *file)
{
	if(init_mlx(mlx, file))
		return (1);
	creat_image(mlx, file);
	mlx_hook(mlx->win, 2, 1L << 0, deal_press_key, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, deal_release_key, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_win, mlx);
	mlx_loop_hook(mlx->init_ptr, render_next_frame, mlx);
	return (0);
}

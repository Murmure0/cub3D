/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:37:44 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/22 14:09:23 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*WIP : ajouter ici tout ce qui doit etre free avant de quitter le programme*/
void free_all(t_file *file, t_mlx *mlx)
{
	(void)file;

	free(mlx->init_ptr);
}

int	close_win(t_mlx *mlx, t_file *file)
{
	(void)file;

	mlx_destroy_window(mlx->init_ptr, mlx->win);
	free_all(file, mlx);
	exit(0);
}

void	init_img(t_mlx *mlx, t_file *file, t_img *img_xpm)
{
	int img_width;
	int img_height;

	img_height = 32;
	img_width = 32;

	img_xpm->ea = mlx_xpm_file_to_image(mlx->init_ptr, file->param->ea,
			&img_width, &img_height);
	img_xpm->we = mlx_xpm_file_to_image(mlx->init_ptr, file->param->we,
			&img_width, &img_height);
	img_xpm->so = mlx_xpm_file_to_image(mlx->init_ptr, file->param->so,
			&img_width, &img_height);
	img_xpm->no = mlx_xpm_file_to_image(mlx->init_ptr, file->param->no,
			&img_width, &img_height);
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
				mlx->player->x_pos = x;
				mlx->player->dx_pos = (double)x;
				mlx->player->y_pos = y;
				mlx->player->dy_pos = (double)y;
			}
		}
	}
}

/*
Initialisation du pointeur mlx, de la fenetre, des xpm, de la position du player
et mise en place des keyhook
*/
int init_mlx(t_mlx *mlx, t_file *file, t_img *img_xpm)
{
	(void)file;
	mlx->init_ptr = mlx_init();
	if(!mlx->init_ptr)
		return (write(2, "Error\nMlx: initialisation failed.\n", 33), 1);
	mlx->win = mlx_new_window(mlx->init_ptr, WIN_W, WIN_H, "Cub3D");
	if (mlx->win == NULL)
			return (write(2, "Error\nMlx: new window init. failed.\n", 36), 1);
	init_img(mlx, file, img_xpm);
	mlx->img = img_xpm;
	init_player(mlx, file);
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
int launch_mlx(t_mlx *mlx, t_file *file, t_img *img_xpm)
{
	if(init_mlx(mlx, file, img_xpm))
		return (1);
	creat_image(mlx, file, img_xpm); //wip : voir put_img.c
	mlx_hook(mlx->win, 2, 1L << 0, deal_press_key, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, deal_release_key, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_win, mlx);
	mlx_loop_hook(mlx->init_ptr, render_next_frame, mlx);
	return (0);
}
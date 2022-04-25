/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:37:44 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/25 19:42:24 by mberthet         ###   ########.fr       */
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
	if (mlx->cam)
		free(mlx->cam);
}

int	close_win(t_mlx *mlx, t_file *file)
{
	(void)file;

	mlx_destroy_window(mlx->init_ptr, mlx->win);
	free_all(file, mlx);
	//system("leaks cub3d");
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


void init_dir(t_mlx *mlx, int x, int y, double player_dir)
{
	mlx->player->dirX = x;
	mlx->player->dirY = y;
	mlx->player->player_dir = player_dir;
}

/*Initialise la direction du player en fontion de la lettre N/S/E/W*/
void	init_dir_player(t_mlx *mlx, t_file *file, int x, int y)
{
	if (file->scene[y][x] == 'N')
		init_dir(mlx, 0, -1, (M_PI/2));
	else if(file->scene[y][x] == 'E')
		init_dir(mlx, 1, 0, 0);
	else if(file->scene[y][x] == 'W')
		init_dir(mlx, -1, 0, M_PI);
	else if(file->scene[y][x] == 'S')
		init_dir(mlx, 0, 1, (3 * M_PI/2));
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
				init_dir_player(mlx, file, x, y);
			}
		}
	}
}

/*
Initialisation du pointeur mlx, de la fenetre, des xpm, de la position du player
et des param de la camera (voir camera.c)
*/
int init_mlx(t_mlx *mlx, t_file *file, t_img *img_xpm)
{
	mlx->cam = malloc((sizeof(t_cam)));
	if (!mlx->cam)
		return (1);
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
	init_img(mlx, file, img_xpm);
	mlx->img = img_xpm;
	init_player(mlx, file);
//	init_cam(mlx, file);
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
	mlx_hook(mlx->win, 2, 1L << 0, deal_press_key, mlx); //wip : pivotage du perso sur la minimap
	mlx_hook(mlx->win, 3, 1L << 1, deal_release_key, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_win, mlx);
	mlx_loop_hook(mlx->init_ptr, render_next_frame, mlx);
	return (0);
}

/*WIP :
- creer un vecteur partant du player dans la direction où il doit regarder
- creer un fuseau de vecteur qui vont evaluer tout ce qui est afficher dans notre ecran, FOV = 60 degré
- calcul de la distance des murs avec DDA or "Digital Differential Analysis" => leur hauteur
*/

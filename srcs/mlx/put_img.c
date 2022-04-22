/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:44:30 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/22 14:09:47 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
Positionne les pixel au bon endroit x/y sur l'image transmise par l'adresse de l'image mlx->addr_img. 
Note : 0/0 en haut a gauche
my_mlx_pixel_put(mlx, 0, 0, 0x00FF0000);
*/
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr_img + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*WIP pour test l'affichage sol/ciel : modifier la methode qd on aura les murs
 Colo ciel : file->param->ceiling
 Colo sol : file->param->floor */
int put_floor_ceiling(t_mlx *mlx, t_file *file)
{
	(void)file;
	int	i;
	int	j;

	i = 0;
	while (i < WIN_W)
	{
		j = 0;
		while (j < WIN_H/2)
		{
			my_mlx_pixel_put(mlx, i, j, 0x00C0BBFF);
			j++;
		}
		i++;
	}
	//inclure la zone de mur ici
	i = 0;
	while (i < WIN_W)
	{
		j = WIN_H/2;
		while (j < WIN_H)
		{
			my_mlx_pixel_put(mlx, i, j, 0x00EEDDCE);
			j++;
		}
		i++;
	}
	return (0);
}

/*
Imprime chaque carré de la minimap de taille SCALE_MAP = 16 pixel de coté
*/
void	print_minimap_square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = x * SCALE_MAP;
	while (i < (x + 1) * SCALE_MAP)
	{
		j = y * SCALE_MAP;
		while (j < (y + 1) * SCALE_MAP)
		{
			if ( i % SCALE_MAP == 0 || j % SCALE_MAP == 0)
				my_mlx_pixel_put(mlx, i, j, 0xAACCCCCC);
			else
				my_mlx_pixel_put(mlx, i, j, color);
			j++;
		}
		i++;
	}
}

/*Parcourt la map parsée dans scene, imprime la minimap en fct des 1 et des 0*/
void	creat_minimap(t_mlx *mlx, t_file *file)
{
	int	x;
	int	y;

	y = -1;
	while (file->scene[++y])
	{
		x = -1;
		while (file->scene[y][++x])
		{
			if (file->scene[y][x] == '1')
				print_minimap_square(mlx, x, y, 0x00000000);
			else if (file->scene[y][x] == '0' || file->scene[y][x] == 'N' ||
					file->scene[y][x] == 'E' || file->scene[y][x] == 'W' ||
					file->scene[y][x] == 'S')
				print_minimap_square(mlx, x, y, 0x00FFFFFF);
		}
	}
	my_mlx_pixel_put(mlx, mlx->player->dx_pos * SCALE_MAP, mlx->player->dy_pos * SCALE_MAP, 0xB22222);
}

/*WIP :
- creer un vecteur allant du player dans la direction où il doit regarder
- creer un fuseau de vecteur qui vont evaluer tout ce qui est afficher dans notre ecran, FOV = 60 degré
- calcul de la distance des murs avec DDA or "Digital Differential Analysis" => leur hauteur
*/

/*Fonctions importantes :
	int	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 20, 20);
		envoie l'image dans la fenetre
	void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
		place un pixel aux coordonnées x / y, de couleur color
*/
void creat_image(t_mlx *mlx, t_file *file, t_img *img_xpm)
{
	(void)mlx;
	(void)file;
	(void)img_xpm;
	mlx->img = mlx_new_image(mlx->init_ptr, WIN_W, WIN_H);
	mlx->addr_img = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);

	put_floor_ceiling(mlx, file); //wip : affichage du sol et du ciel
	creat_minimap(mlx, file); //wip : affichage de la minimap + player
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
}


/*
lors d'un event va calculer et push la nouvelle image dans la fenetre
*/
int	render_next_frame(t_mlx *mlx)
{
	put_floor_ceiling(mlx, mlx->file); //wip : affichage du sol et du ciel
	creat_minimap(mlx, mlx->file); //wip : affichage de la minimap + player
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
	return (0);
}
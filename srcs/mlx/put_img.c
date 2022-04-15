/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:44:30 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/15 18:49:47 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

/*Positionne les pixel au bon endroit x/y. Note : 0/0 en haut a gauche
my_mlx_pixel_put(mlx, 0, 0, 0x00FF0000);*/
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
	mlx_put_image_to_window(mlx->init_ptr, mlx->win, mlx->img, 0, 0);
	return (0);
}

/*WIP*/
void creat_image(t_mlx *mlx, t_file *file)
{
	(void)mlx;
	(void)file;
	mlx->img = mlx_new_image(mlx->init_ptr, WIN_W, WIN_H);
	mlx->addr_img = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);

	put_floor_ceiling(mlx, file); //wip
}

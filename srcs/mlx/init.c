/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:37:44 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/15 18:48:35 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void free_all(t_file *file, t_mlx *mlx)
{
	(void)file;

	free(mlx->init_ptr);
}

int	close_win(t_mlx *mlx, t_file *file)
{
	(void)file;

	//mlx_destroy_image(mlx->init_ptr, mlx->img);
	mlx_destroy_window(mlx->init_ptr, mlx->win);
	free_all(file, mlx);
	exit(0);
}

/*keys : W,A,S,D && left & righ : WIP
creation  de fonctions qui reactualiseront la position du perso + les images a l'ecran qd une touche est appuyee*/
int	deal_key(int keycode, t_mlx *mlx, t_file *file)
{
	(void)file;
	if (keycode == 53)
	{
		//mlx_destroy_image(mlx->init_ptr, mlx->img);
		mlx_destroy_window(mlx->init_ptr, mlx->win);
		free_all(file, mlx);
		exit(0);
	}
	// else if (keycode == 13)
	// 	move_up(mlx, file);
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

int init_mlx(t_mlx *mlx, t_file *file)
{
	(void)file;
	mlx->init_ptr = mlx_init();
	if(!mlx->init_ptr)
		return (write(2, "Error\nMlx: initialisation failed.\n", 33), 1);
	mlx->win = mlx_new_window(mlx->init_ptr, WIN_W, WIN_H, "Cub3D");
	if (mlx->win == NULL)
			return (write(2, "Error\nMlx: new window init. failed.\n", 36), 1);
	mlx_hook(mlx->win, 2, 1L << 0, deal_key, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, close_win, mlx);
	return (0);
}

int launch_mlx(t_mlx *mlx, t_file *file)
{
	if(init_mlx(mlx, file))
		return (1);
	creat_image(mlx, file); //wip : voir put_img.c
	
	//imprimer le ciel & le sol sur une image puis
	//imprimer dessus les objets demande un double calcul pour certaines zones => jeu - fluide
	//solution : imprimer d'abord les objets puis remplir le reste avec le ciel & le sol

	//utiliser 2 image pour le calcul des nouvelles img, on les put_image_to_win en alternance
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:58:45 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/25 19:25:39 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

// int	init_cam(t_cam *cam, t_file *file, t_mlx *mlx)
// {
// 	(void)file;
// 	int	x;
// 	int w = 1;

// 	x = 0;
// 	cam->planeX = 0;
// 	cam->planeY = 0.66;

// 	while(x < w)
// 	{
// 		cam->cameraX = 2 * x / (double)w - 1;
// 		cam->rayDirX = player->dirX + cam->planeX * cam->cameraX;

// 		cam->mapX = mlx->player->x_pos;
// 		cam->mapY = mlx->player->y_pos;

// 		x++;
// 	}
// 	//WIP : initialisation des variables dans mlx->cam a partir du tuto,
// 	// a partir de la phrase "Here starts the actual raycasting."
// 	//verifier si des variables declarees dans cam ne sont pas deja existantes dans mlx->player

// 	/*WIP :
// - creer un vecteur partant du player dans la direction où il doit regarder
// - creer un fuseau de vecteur qui vont evaluer tout ce qui est afficher dans notre ecran, FOV = 60 degré
// - calcul de la distance des murs avec DDA or "Digital Differential Analysis" => leur hauteur
// */

// 	return (0);
// }


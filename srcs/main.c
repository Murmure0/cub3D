/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:18:49 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/21 17:24:47 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main (int ac, char **av)
{
	t_file file;
	t_mlx mlx;
	t_img img_xpm;

	if (parse_file(&file, ac, av))
		return(1);

	if(launch_mlx(&mlx, &file, &img_xpm))
		return (1);
	mlx_loop(mlx.init_ptr);
	printf("coucou\n");
	//system("leaks cub3d");
	return (0);
}

//TODO

//FINIR PARSING

//POINT COLLISION AVEC MUR
//AFFICHER 1 RAY COMPLET
//AFFICHER 2 FAISEAUX, 1X -30 DEGR  1X +30DEGR POUR PT OF VIEW
//CALCULER HAUTEUR DES MURS A AFFICHER, INVERSEMENT PROPORTIONNEL A LA DISTANCE DU RAY.
//3D
//DETECTER ORIENTATION MUR TOUCHE PAR RAY
// (textures)
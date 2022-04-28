/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:58:45 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/27 14:48:50 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

/*Place le vecteur dans la direction initiale du joueur
WIP : ne sait pas encore s'adapter a la rotation du joueur*/
int put_ray(t_file *file, t_mlx *mlx, t_player *player) 
{
	(void)mlx;
	double dirX = cos(player->player_dir);
	double dirY = sin(player->player_dir);
	double deltaX = player->dx_pos + dirX;
	double deltaY = player->dy_pos - dirY;

	//printf("valeur de cos(dir) : %f, valeur de sin(dir) : %f\n", cos(player->player_dir), sin(player->player_dir));
	if (dirX < 0.000000 && dirY >= 0.000000) //ouest
	{
		deltaX += 1; //pour que ça commence bien a partir du player
		while(file->scene[(int)deltaY][(int)(deltaX - SPEED)] != '1')
		{
			my_mlx_pixel_put(mlx, (deltaX) * SCALE_MAP, deltaY * SCALE_MAP, 0x84DBF0);
			deltaX -= SPEED; // WIP : remplacer cette etape par le DDA ici
		}
	}

	if (dirX >= 0.000000 && dirY <= 0.000000) //est
	{
		deltaX -= 1;
		while(file->scene[(int)deltaY][(int)(deltaX + SPEED)] != '1')
		{
			my_mlx_pixel_put(mlx, deltaX * SCALE_MAP, deltaY * SCALE_MAP, 0x84DBF0);
			deltaX += SPEED;// WIP : et ici
		}
	}
	
	if (dirX <= 0.000000 && dirY < 0.000000) //sud
	{
		deltaY -= 1;
		while(file->scene[(int)(deltaY + SPEED)][(int)(deltaX)] != '1')
		{
			my_mlx_pixel_put(mlx, deltaX * SCALE_MAP, deltaY * SCALE_MAP, 0x84DBF0);
			deltaY += SPEED;// WIP : et la
		}
	}

	if (dirX >= 0 && dirY > 0) //nord
	{
		deltaY += 1;
		while(file->scene[(int)(deltaY - SPEED)][(int)(deltaX)] != '1')
		{
			my_mlx_pixel_put(mlx, deltaX * SCALE_MAP, deltaY * SCALE_MAP, 0x84DBF0);
			deltaY -= SPEED; // WIP : mais bon on peut pe opti tout ça
		}
	}
	return (0);
}


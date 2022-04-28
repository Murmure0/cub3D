/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:58:45 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/28 18:21:52 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

/*WIP : 
- print_ray : adapter le theoreme de Bresenham pour savoir tracer les vecteurs  point par point, 
		en fonction du point d'arriver et de depart + la pente
- put_first_ray : s'assurer que le point final arrive bien là où il doit, semble devier sur l'axe X
*/

void	init_ray(t_ray *ray, t_player *player)
{
	ray->r_x_pos = player->x_pos;
	ray->r_y_pos = player->y_pos;
	ray->r_dx_pos = player->dx_pos;
	ray->r_dy_pos = player->dy_pos;
	ray->r_player_dir = player->player_dir;
	ray->r_dirX = cos(player->player_dir);
	ray->r_dirY = sin(player->player_dir);
	ray->r_ray_unit_step_side_x = sqrt(1 + pow((ray->r_dirY/ray->r_dirX), 2.0));
	ray->r_ray_unit_step_side_y = sqrt(1 + pow((ray->r_dirX/ray->r_dirY), 2.0));
	ray->r_map_check_x = ray->r_x_pos;
	ray->r_map_check_y = ray->r_y_pos;
	ray->r_raylength_x = 0;
	ray->r_raylength_y = 0;
	ray->r_step_x = (int)ray->r_raylength_x;
	ray->r_step_y = (int)ray->r_raylength_y;
	ray->r_dist_x = 0;
	ray->r_dist_y = 0;
}

int	check_high_tab(t_file *file)
{
	int high_tab;
	int i;
	int j;

	high_tab = 0;
	j = 0;
	while (file->scene[j])
	{
		i = 0;
		while (file->scene[j][i])
		{
			i++;
		}
			high_tab++;
		j++;
	}
	//printf("valeur de high tab : %d\n", high_tab);
	return (high_tab);
}

// void	print_ray(t_ray *ray, t_player *player, t_mlx *mlx) //WIP : savoir tracer les rayons venant du joueur au point final, voir : algo de tracé de segment de Bresenham
// {

// 	double x = (player->dx_pos);
// 	double y = (player->dy_pos );
// 	my_mlx_pixel_put(mlx, (player->dx_pos) * SCALE_MAP, (player->dy_pos ) * SCALE_MAP, 0x333333);

// 	my_mlx_pixel_put(mlx, x * SCALE_MAP, y * SCALE_MAP, 0x333333);

// 	my_mlx_pixel_put(mlx, ray->hit_x * SCALE_MAP, ray->hit_y * SCALE_MAP, 0x333333);
// }

void	put_first_ray(t_file *file, t_mlx *mlx, t_player *player, t_ray *ray) //tracer de ray
{
	(void)file;
	(void)mlx;
	int	hit;
	int high_tab;

	high_tab = check_high_tab(file);
	hit = 0;
	init_ray(ray, player);
	// printf("OUOU : raylenghtX : %f, rayunitstepside x : %f\n",ray->r_raylength_x, ray->r_ray_unit_step_side_x);
	// printf("OUOU : playerdir : %f, r_dirX : %f,r_dirXY : %f\n",ray->r_player_dir, ray->r_dirX,ray->r_dirY);

	/*Savoir sur quel axe on commence a se deplacer*/
	if (ray->r_dirX < 0)
	{
		ray->r_step_x -=1;
		ray->r_raylength_x = (ray->r_dx_pos - (double)(ray->r_map_check_x)) * ray->r_ray_unit_step_side_x;
	}
	else
	{
		ray->r_step_x = 1;
		ray->r_raylength_x = ((double)(ray->r_map_check_x) - ray->r_dx_pos) * ray->r_ray_unit_step_side_x;
	}
	if (ray->r_dirY < 0)
	{
		ray->r_step_y =1;
		ray->r_raylength_y = ((double)(ray->r_map_check_y) - ray->r_dy_pos) * ray->r_ray_unit_step_side_y;
	}
	else
	{
		ray->r_step_y -= 1;
		ray->r_raylength_y = (ray->r_dy_pos - (double)(ray->r_map_check_y)) * ray->r_ray_unit_step_side_y;
	} // check sur y si cest + ou - pour monter et descendre

	/*Tant qu'on a pas atteint de mur on avance sur les deux axes alternativements*/
	while (!hit)
	{
		if (ray->r_raylength_x < ray->r_raylength_y)
		{
			ray->r_map_check_x += ray->r_step_x;
			ray->r_dist_x = ray->r_raylength_x;
			ray->r_raylength_x += ray->r_ray_unit_step_side_x;
		}
		else
		{
			ray->r_map_check_y += ray->r_step_y;
			ray->r_dist_y = ray->r_raylength_y;
			ray->r_raylength_y += ray->r_ray_unit_step_side_y;
		}
		my_mlx_pixel_put(mlx, ray->r_map_check_x * SCALE_MAP, ray->r_map_check_y * SCALE_MAP, 0xB22222); /*trace sur les points d'intersections*/
		if (ray->r_map_check_y >= 0 && ray->r_map_check_y < high_tab
				&& ray->r_map_check_x >= 0 && (size_t)ray->r_map_check_x < (ft_strlen(file->scene[ray->r_map_check_y - 1]))) //on ne veut pas sortir de la map
		{
			if (file->scene[ray->r_map_check_y][(ray->r_map_check_x + ray->r_step_x)] == '1' ||
				file->scene[(ray->r_map_check_y + ray->r_step_y)][ray->r_map_check_x] == '1') //on a trouvé un mur 
			{
				hit = 1;
				break ;
			}
		}
		else
			break;
	}

	if (hit == 1) //on a trouver notre point final d'impact sur le mur et on a ses coordonnees dans hit x et hit y
	{
		ray->hit_x = ray->r_dx_pos + ray->r_dirX * ray->r_raylength_x;
		ray->hit_y = ray->r_dy_pos - ray->r_dirY * ray->r_raylength_y;
		// ray->hit_x = ray->r_dirX + ray->r_player_dir * ray->r_dist_x;
		// ray->hit_y = ray->r_dirY + ray->r_player_dir * ray->r_dist_y;
		//printf("valeur de hit x : %f, valeur de hit y : %f\nr_dirx : %f, r_dirY : %f\nplayer dir : %f\ndist x : %f dist y : %f\n",ray->hit_x,ray->hit_y, ray->r_dirX,ray->r_dirY,ray->r_player_dir, ray->r_dist_x,ray->r_dist_y);
	}

	my_mlx_pixel_put(mlx, ray->hit_x * SCALE_MAP, ray->hit_y * SCALE_MAP, 0xB22222);
	//print_ray(ray, player, mlx);
	//put_ray(file, mlx, player, ray)
}

/*Ancienne ft pour tracer des vecteurs en ligne droite selon N/S/O/E*/
// int put_ray(t_file *file, t_mlx *mlx, t_player *player)
// {
// 	(void)mlx;
// 	double dirX = cos(player->player_dir);
// 	double dirY = sin(player->player_dir);
// 	double deltaX = player->dx_pos + dirX;
// 	double deltaY = player->dy_pos - dirY;

// 	printf("valeur de cos(dir) : %f, valeur de sin(dir) : %f\n", cos(player->player_dir), sin(player->player_dir));
// 	if (dirX < 0.000000 && dirY >= 0.000000) //ouest
// 	{
// 		deltaX += 1; //pour que ça commence bien a partir du player
// 		while(file->scene[(int)deltaY][(int)(deltaX - SPEED)] != '1')
// 		{
// 			my_mlx_pixel_put(mlx, (deltaX) * SCALE_MAP, deltaY * SCALE_MAP, 0x84DBF0);
// 			deltaX -= SPEED * ; // WIP : remplacer cette etape par le DDA ici
// 		}
// 	}

// 	if (dirX >= 0.000000 && dirY <= 0.000000) //est
// 	{
// 		deltaX -= 1;
// 		while(file->scene[(int)deltaY][(int)(deltaX + SPEED)] != '1')
// 		{
// 			my_mlx_pixel_put(mlx, deltaX * SCALE_MAP, deltaY * SCALE_MAP, 0x84DBF0);
// 			deltaX += SPEED;// WIP : et ici
// 		}
// 	}

// 	if (dirX <= 0.000000 && dirY < 0.000000) //sud
// 	{
// 		deltaY -= 1;
// 		while(file->scene[(int)(deltaY + SPEED)][(int)(deltaX)] != '1')
// 		{
// 			my_mlx_pixel_put(mlx, deltaX * SCALE_MAP, deltaY * SCALE_MAP, 0x84DBF0);
// 			deltaY += SPEED;// WIP : et la
// 		}
// 	}

// 	if (dirX >= 0 && dirY > 0) //nord
// 	{
// 		deltaY += 1;
// 		while(file->scene[(int)(deltaY - SPEED)][(int)(deltaX)] != '1')
// 		{
// 			my_mlx_pixel_put(mlx, deltaX * SCALE_MAP, deltaY * SCALE_MAP, 0x84DBF0);
// 			deltaY -= SPEED; // WIP : mais bon on peut pe opti tout ça
// 		}
// 	}
// 	return (0);

// }


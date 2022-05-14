/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:58:45 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/13 16:49:50 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*Initialize ray struct */
static void	init_ray(t_ray *ray, t_player *player, double ray_angle)
{
	ray->p_dy_pos = player->dy_pos;
	ray->p_dx_pos = player->dx_pos;
	ray->p_map_check_x = (int)ray->p_dx_pos;
	ray->p_map_check_y = (int)ray->p_dy_pos;
	ray->r_dir_x = cos(ray_angle);
	ray->r_dir_y = sin(ray_angle);
	ray->r_step_size_x = sqrt(1.0 + pow(ray->r_dir_y / ray->r_dir_x, 2));
	ray->r_step_size_y = sqrt(1.0 + pow(ray->r_dir_x / ray->r_dir_y, 2));
	ray->r_len_x = 0;
	ray->r_len_y = 0;
	ray->r_dist = 0;
	ray->hit = 0;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->side = 0;
}

/* Identify which axis the wall will be searched on */
static void	init_dir_ray(t_ray *ray)
{
	if (ray->r_dir_x < 0)
	{
		ray->r_step_x = -1;
		ray->r_len_x = (ray->p_dx_pos - ((double)ray->p_map_check_x))
			* ray->r_step_size_x;
	}
	else
	{
		ray->r_step_x = 1;
		ray->r_len_x = ((double)(ray->p_map_check_x + 1) - ray->p_dx_pos)
			* ray->r_step_size_x;
	}
	if (ray->r_dir_y < 0)
	{
		ray->r_step_y = -1;
		ray->r_len_y = (ray->p_dy_pos - (double)ray->p_map_check_y)
			* ray->r_step_size_y;
	}
	else
	{
		ray->r_step_y = 1;
		ray->r_len_y = ((double)(ray->p_map_check_y + 1) - ray->p_dy_pos)
			* ray->r_step_size_y;
	}
}

/* Increment x && y until a wall is found */
static void	find_wall(int dist_max, t_ray *ray, t_file *file)
{
	while (ray->hit != 1 && ray->r_dist < dist_max)
	{
		if (ray->r_len_x < ray->r_len_y)
		{
			ray->p_map_check_x += ray->r_step_x;
			ray->r_dist = ray->r_len_x;
			ray->r_len_x += ray-> r_step_size_x;
			ray->side = 0;
		}
		else
		{
			ray->p_map_check_y += ray->r_step_y;
			ray->r_dist = ray->r_len_y;
			ray->r_len_y += ray->r_step_size_y;
			ray->side = 1;
		}
		if (ray->p_map_check_x >= 0 && ray->p_map_check_x < file->map_w
			&& ray->p_map_check_y >= 0 && ray->p_map_check_y < file->map_h)
		{
			if (file->scene[ray->p_map_check_y][ray->p_map_check_x] == '1')
			{
				ray->hit = 1;
			}
		}
	}
}

static double	around_circle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	put_first_ray(t_file *file, t_mlx *mlx, t_player *player, t_ray *ray)
{
	double	ray_angle;
	double	cam_angle;
	int		dist_max;
	int		x;

	x = (0 - WIN_W * 0.5);
	while (x < WIN_W * 0.5)
	{
		ray_angle = around_circle(player->player_dir + (double)x
				* ((double)66 / WIN_W) * (M_PI / 180));
		cam_angle = around_circle((double)x *((double)66 / WIN_W)
				* (M_PI / 180));
		init_ray(ray, player, ray_angle);
		init_dir_ray(ray);
		if (file->map_w > file->map_h)
			dist_max = file->map_w;
		else
			dist_max = file->map_h;
		find_wall(dist_max, ray, file);
		wall_line_len(ray, cam_angle);
		draw_col(mlx, ray, x + WIN_W / 2);
		x++;
	}
}

// void	put_first_ray(t_file *file, t_mlx *mlx, t_player *player, t_ray *ray) //tracer de ray
// {
// 	double	ray_angle;
// 	int		dist_max;
// 	double	wall_len;
// 	double	len;
// 	int		x;

// 	ray_angle = player->player_dir - (33 * M_PI/180); //on retranche 30deg a l'angle du player pour commencer le cone a G
// 	if (ray_angle < 0)
// 		ray_angle += 2 * M_PI;
// 	if (ray_angle > 2 * M_PI) //si on est passé au dela de 1 tour complet on reajuste
// 		ray_angle -= 2 * M_PI;
// 	x = (0 - WIN_W / 2); //on divise l'ecran en 2, x commence tout a gauche
// 	while (x < WIN_W / 2) //tant qu'on arrive pas a la droite de l'ecran
// 	{
// 		init_ray(ray, player, ray_angle); //init une structure par ray
// 		init_dir_ray(ray); //on toruve la dir du ray
// 		dist_max = find_distmax(file);
// 		find_wall(dist_max, ray, file); //calcul de la distance au mur : hit : point d'intersection ray/mur
// 		if (ray->hit == 1)
// 		{
// 			ray->hit_x = ray->p_dx_pos + ray->r_dir_x * ray->r_dist;
// 			ray->hit_y = ray->p_dy_pos + ray->r_dir_y * ray->r_dist;
// 		}
// 		//my_mlx_pixel_put(mlx, ray->hit_x *SCALE_MAP, ray->hit_y *SCALE_MAP, 0x00FF00FF); //print le point d'intersection entre le ray et le mur
		
// 		len = sqrt(pow((ray->hit_x - ray->p_dx_pos), 2) + pow((ray->hit_y - ray->p_dy_pos), 2)); //pythagore pour connaitre la hauteur du mur

// 		wall_len = len * cos(ray_angle - player->player_dir); //correction fisheyes

		
// 		ray->line_len = (WIN_H / wall_len); //hauteur perçue du mur : hauteur de la ligne a imprimer

// 		draw_col(mlx, ray, x + WIN_W / 2); //impression ciel/mur/sol
// 		ray_angle += (66 * M_PI/180)/(double)WIN_W; //faire varier l'angle pour passer a la colonne d'a coté
// 		x++; //on ++ pour indiquer a quel endroit de la fenetre on devra imprimer le prochain ray
// 	}
// }

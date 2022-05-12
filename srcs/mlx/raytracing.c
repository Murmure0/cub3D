/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:58:45 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/12 11:26:07 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

/*Initialise la struct dediee aux rayons*/
void	init_ray(t_ray *ray, t_player *player, double ray_angle)
{
	ray->p_dy_pos = player->dy_pos; ray->p_dx_pos = player->dx_pos; //position player X
	// Y
	ray->p_map_check_x = (int)ray->p_dx_pos; //player sur map
	ray->p_map_check_y = (int)ray->p_dy_pos;
	ray->r_dir_x = cos(ray_angle); //dir de l'angle
	ray->r_dir_y = sin(ray_angle);
	ray->r_step_size_x = sqrt(1.0 + pow(ray->r_dir_y/ray->r_dir_x, 2)); //progression sur axe X
	ray->r_step_size_y = sqrt(1.0 + pow(ray->r_dir_x/ray->r_dir_y, 2));
	ray->r_len_x = 0;
	ray->r_len_y = 0;
	ray->r_dist = 0;
	ray->hit = 0;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->side = 0;
}

/*identifie sur quel direction de chaque axe on va commencer a chercher un mur*/
void init_dir_ray(t_ray *ray)
{
	if (ray->r_dir_x < 0)
	{
		ray->r_step_x = -1;
		ray->r_len_x = (ray->p_dx_pos - ((double)ray->p_map_check_x)) * ray->r_step_size_x; //longueur entre deux segments
	}
	else
	{
		ray->r_step_x = 1;
		ray->r_len_x = ((double)(ray->p_map_check_x + 1) - ray->p_dx_pos) * ray->r_step_size_x;
	}
	if (ray->r_dir_y < 0)
	{
		ray->r_step_y = -1;
		ray->r_len_y = (ray->p_dy_pos - (double)ray->p_map_check_y) * ray->r_step_size_y;
	}
	else
	{
		ray->r_step_y = 1;
		ray->r_len_y = ((double)(ray->p_map_check_y + 1) - ray->p_dy_pos) * ray->r_step_size_y;
	}
}

int find_distmax(t_file * file)
{
	int dist_max;

	if (file->map_w > file->map_h)
		dist_max = file->map_w;
	else
		dist_max = file->map_h;
	return(dist_max);
}

/*On avance sur x & y until wall*/
void	find_wall(int dist_max, t_ray *ray, t_file * file)
{
	while (ray->hit != 1 && ray->r_dist < dist_max)
	{
		if (ray->r_len_x < ray->r_len_y)
		{
			ray->p_map_check_x += ray->r_step_x;
			ray->r_dist = ray->r_len_x;
			ray->r_len_x +=ray-> r_step_size_x;
			ray->side = 0; // on touche un mur sur l'axe X : O ou E
		}
		else
		{
			ray->p_map_check_y += ray->r_step_y;
			ray->r_dist = ray->r_len_y;
			ray->r_len_y += ray->r_step_size_y;
			ray->side = 1; //On touche S ou N
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

int	dir_wall(t_ray *ray)
{
	if (ray->side == 0 && ray->r_dir_x < 0) //rouge ouest
		return(WEST);
	else if (ray->side == 0 && ray->r_dir_x > 0) //vert est
		return(EST);
	else if (ray->side == 1 && ray->r_dir_y < 0) // bleu sud
		return(SOUTH);
	else // rose nord
		return(NORTH);

}

int	find_col(t_mlx *mlx, t_ray *ray, int dir)
{
	int	col;

	col = 0;
	if (dir == WEST)
		col = (int)((1.0 - (ray->hit_y - (int)ray->hit_y)) * (float)mlx->txt[dir].w);
	else if (dir == EST)
		col = (int)(((ray->hit_y - (int)ray->hit_y)) * (float)mlx->txt[dir].w);
	else if (dir == SOUTH)
		col = (int)(((ray->hit_x - (int)ray->hit_x)) * (float)mlx->txt[dir].w);
	else if (dir == NORTH)
		col = (int)((1.0 - (ray->hit_x - (int)ray->hit_x)) * (float)mlx->txt[dir].w);
	if (col >= mlx->txt[dir].w)
	{
		col = mlx->txt[dir].w - 1;
	}
	return (col);
}

int	draw_wall(t_mlx *mlx, t_ray *ray, int x, double ray_angle)
{
	(void)ray_angle;
	int		dir;
	int		col;
	int		d_wall;
	double	text_x;
	double	text_x_step;

	// int i = 0;
	// int j = 0;

	d_wall = (int)((WIN_H / 2.0) + (ray->line_len / 2.0));

	dir = dir_wall(ray);
	col = find_col(mlx, ray, dir);

	text_x = 0.00; // premiere texel
	text_x_step = (mlx->txt[dir].h - 1) / ray->line_len; // ratio pour savoir quel texel imprimer
	while(ray->h_wall < d_wall)
	{
		if (ray->h_wall >= 0 && ray->h_wall <= WIN_H -1)
			my_mlx_pixel_put(mlx, x, ray->h_wall, get_texel_color(&mlx->txt[dir], col, text_x));
		ray->h_wall++;
		text_x += text_x_step;
	}
	return(0);
}

/*Print ciel/mur/sol*/
// void	draw_col(t_mlx *mlx, t_ray *ray, int x, double line_len)
void	draw_col(t_mlx *mlx, t_ray *ray, int x, double ray_angle)
{
	(void)ray_angle;
	int i;

	i = 0;
	ray->h_wall = (int)((WIN_H / 2.0) - (ray->line_len / 2.0));

	while (i < ray->h_wall)
	{
		if (i >=0 && i < ray->h_wall)
			my_mlx_pixel_put(mlx, x, i, mlx->file->param->ceiling);
		i++;
	}
//ICI
	i = draw_wall(mlx, ray, x, ray_angle);
	
	while (i < WIN_H - 1)
	{
		if (i >= ray->h_wall && i < WIN_H - 1)
			my_mlx_pixel_put(mlx, x, i, mlx->file->param->floor);
		i++;
	}
}

void	put_first_ray(t_file *file, t_mlx *mlx, t_player *player, t_ray *ray) //tracer de ray
{
	(void)file;
	(void)mlx;

	double ray_angle;
	int dist_max;
	double wall_len;
	double len;

	//ray_angle = player->player_dir - (M_PI/6); //on retranche 30deg a l'angle du player pour commencer le cone a G

	ray_angle = player->player_dir - (M_PI/6); //on retranche 30deg a l'angle du player pour commencer le cone a G
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	if (ray_angle > 2 * M_PI) //si on est passé au dela de 1 tour complet on reajuste
		ray_angle -= 2 * M_PI;


	int x = (0 - WIN_W / 2); //on divise l'ecran en 2, x commence tout a gauche

	while (x < WIN_W / 2) //tant qu'on arrive pas a la droite de l'ecran
	{
		init_ray(ray, player, ray_angle); //init une structure par ray
		init_dir_ray(ray); //on toruve la dir du ray
		dist_max = find_distmax(file);
		find_wall(dist_max, ray, file); //calcul de la distance au mur : hit : point d'intersection ray/mur

		if (ray->hit == 1)
		{
			ray->hit_x = ray->p_dx_pos + ray->r_dir_x * ray->r_dist;
			ray->hit_y = ray->p_dy_pos + ray->r_dir_y * ray->r_dist;
		}
		my_mlx_pixel_put(mlx, ray->hit_x *SCALE_MAP, ray->hit_y *SCALE_MAP, 0x00FF00FF); //print le point d'intersection entre le ray et le mur
		len = sqrt(pow((ray->hit_x - ray->p_dx_pos), 2) + pow((ray->hit_y - ray->p_dy_pos), 2)); //pythagore pour connaitre la hauteur du mur
		wall_len = len * cos(ray_angle - player->player_dir); //correction fisheyes


		ray->line_len = (WIN_H / wall_len); //hauteur perçue du mur : hauteur de la ligne a imprimer

	//ICI : 
		draw_col(mlx, ray, x + WIN_W/2, ray_angle); //impression ciel/mur/sol

		//ray_angle += (60/(double)WIN_W) * M_PI / 180; //faire varier l'angle pour passer a la colonne d'a coté
		ray_angle += (M_PI/3)/(double)WIN_W; //faire varier l'angle pour passer a la colonne d'a coté
		x++; //on ++ pour indiquer a quel endroit de la fenetre on devra imprimer le prochain ray
	}
}

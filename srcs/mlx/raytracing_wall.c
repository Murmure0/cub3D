/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:50:31 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/16 13:28:04 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	get_texel_color(t_txt *txt, int x, int y)
{
	int		color;
	char	*dst;

	dst = txt->txt_adr + (y * txt->len + x * (txt->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

static int	dir_wall(t_ray *ray)
{
	if (ray->side == 0 && ray->r_dir_x < 0)
		return (EAST);
	else if (ray->side == 0 && ray->r_dir_x > 0)
		return (WEST);
	else if (ray->side == 1 && ray->r_dir_y < 0)
		return (SOUTH);
	else
		return (NORTH);
}

/* print the right column of texture pixels to create the walls */
static int	draw_wall(t_mlx *mlx, t_ray *ray, int x)
{
	int		dir;
	int		col;
	int		d_wall;
	double	text_x;
	double	text_x_step;

	d_wall = (int)((WIN_H + ray->line_len) * 0.5);
	dir = dir_wall(ray);
	col = (int)((ray->hit_x + ray->hit_y) * mlx->txt[dir].w) % mlx->txt[dir].w;
	text_x = 0.00;
	text_x_step = (mlx->txt[dir].h - 1) / (double)ray->line_len;
	while (ray->h_wall < d_wall)
	{
		if (ray->h_wall >= 0 && ray->h_wall <= WIN_H - 1)
			my_mlx_pixel_put(mlx, x, ray->h_wall,
				get_texel_color(&mlx->txt[dir], col, (int)text_x));
		ray->h_wall++;
		text_x += text_x_step;
	}
	return (ray->h_wall);
}

/* Print roof/walls/floors */
void	draw_col(t_mlx *mlx, t_ray *ray, int x)
{
	int	i;

	i = 0;
	ray->h_wall = (int)((WIN_H - ray->line_len) * 0.5);
	while (i < ray->h_wall)
	{
		my_mlx_pixel_put(mlx, x, i, mlx->file->param->ceiling);
		i++;
	}
	i = draw_wall(mlx, ray, x);
	while (i < WIN_H - 1)
	{
		my_mlx_pixel_put(mlx, x, i, mlx->file->param->floor);
		i++;
	}
}

// Calculate height of wall to be printed
void	wall_line_len(t_ray *ray, double cam_angle)
{	
	double	len;
	double	wall_len;

	if (ray->hit == 1)
	{
		ray->hit_x = ray->p_dx_pos + ray->r_dir_x * ray->r_dist;
		ray->hit_y = ray->p_dy_pos + ray->r_dir_y * ray->r_dist;
	}
	len = sqrt(pow((ray->hit_x - ray->p_dx_pos), 2)
			+ pow((ray->hit_y - ray->p_dy_pos), 2));
	wall_len = len * cos(cam_angle);
	ray->line_len = (int)(WIN_H / wall_len);
}

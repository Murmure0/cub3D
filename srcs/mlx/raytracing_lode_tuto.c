/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_lode_tuto.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:58:45 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/02 18:49:20 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"


void	raytracing(t_player *player, t_file *file, t_mlx *mlx)
{
	int x = -1;
	int array_x_len = WIN_W;
	//int array_x_len = 10;

	while (++x < array_x_len) //map width = len of longest string in map
	{
		double posX = player->dx_pos;
		double posY = player->dy_pos;
		double dirX = cos(player->player_dir);
		double dirY = sin(player->player_dir);
		
		double cameraX = 2 * x / (double)array_x_len - 1;
		double rayDirX = dirX + mlx->player->planeX * cameraX;
		double rayDirY = dirY + mlx->player->planeY * cameraX;

		int mapX = (int)posX;
		int mapY = (int)posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = sqrt(pow((1 / rayDirX), 2.0));
		double deltaDistY = sqrt(pow((1 / rayDirY), 2.0));
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		 else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		else
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		

		while (hit == 0)
		{
			
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//check 
			if (file->scene[mapY][mapX +stepX] == '1' ||file->scene[mapY + stepY][mapX] == '1')
			{
				hit = 1;
			}
		}
				//printf("MAP COORDS x %c\n, x%d, y%d\n", file->scene[mapY][mapX], mapX, mapY);

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
      	else
			perpWallDist = (sideDistY - deltaDistY);

		
		// mapX++;
		// mapY--;
	
		// double xdbl = mapX;
		// double ydbl = mapY;
		// double i = -1;
		// while (++i < 3)
		// {
		// 	double j = -2;
		// 	while (j++ < 1)
		// 	{
		// 		my_mlx_pixel_put(mlx, xdbl * SCALE_MAP - 1.0 + i, ydbl * SCALE_MAP + j, 0x60f542);
		// 	}
		// }

		int h = WIN_H;
		int lineHeight = (int)(h / perpWallDist);

		// //calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		// //draw the pixels of the stripe as a vertical line
		int k;
		double wall_pixel_size = WIN_W / array_x_len;
		double l = -1;
		while (++l < wall_pixel_size)
		{
			k = drawStart;
			//put_ceiling(mlx, file, k, l);
			while (k < drawEnd)
			{
				if (side == 0 && rayDirX < 0) //ouest 
					my_mlx_pixel_put(mlx, l + (wall_pixel_size * x ), k, 0x0003a3);
				else if (side == 0 && rayDirX > 0) //est
					my_mlx_pixel_put(mlx, l + (wall_pixel_size * x ), k, 0xa30000);
				else if (side == 1 && rayDirY < 0) // sud
					my_mlx_pixel_put(mlx, l + (wall_pixel_size * x ), k, 0xf0b54f);
				else if (side == 1 && rayDirY > 0) // nord
					my_mlx_pixel_put(mlx, l + (wall_pixel_size * x ), k, 0x4ff0c0);
				k++;
			}
			//put_floor(mlx, file, k, l);
		}
	}
}

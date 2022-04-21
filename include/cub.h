/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/21 17:25:59 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define WIN_H 1080
# define WIN_W 1920
# define SCALE_MAP 16

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "mlx.h"

typedef struct s_params
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		ceiling;
	int		floor;
}				t_params;

typedef struct s_file
{
	t_list	*map;
	char	**scene;
	t_params param[1];
}				t_file;

typedef struct s_img {
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
}			t_img;

typedef struct s_player{
	int	x_pos;
	int	y_pos;
}	t_player;

typedef struct s_mlx
{
	void	*init_ptr;
	void	*win;
	void	*img;
	char	*addr_img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_img	*img_xpm;
	t_file	*file;
	t_player	player[1];
}	t_mlx;


/* --- PARSING --- */

int parse_file(t_file *file, int ac, char **av);
int	check_params(t_file *file);

// check_walls
int	not_walled_in(t_file *file);

// parse_utils
int		convert_list_to_array(t_file *file);
int		check_for_newline(t_list *map);
int		parse_spaces(char *str);
int		missing_param(t_params *param);
void	free_param_chains(t_file *f, t_list *head);

/* --- MLX --- */
/* -- init.c -- */
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		launch_mlx(t_mlx *mlx, t_file *file, t_img *img);
int		init_mlx(t_mlx *mlx, t_file *file, t_img *img_xpm);
int		close_win(t_mlx *mlx, t_file *file);
void	free_all(t_file *file, t_mlx *mlx);

/* -- put_img.c -- */
void	creat_image(t_mlx *mlx, t_file *file, t_img *img_xpm);
void	creat_minimap(t_mlx *mlx, t_file *file);

/* -- move.c -- */
int		deal_key(int keycode, t_mlx *mlx);

# endif

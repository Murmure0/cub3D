/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/22 14:09:49 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

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

# define WIN_H 1080
# define WIN_W 1920
# define SCALE_MAP 16
# define SPEED 0.05
# define FOV 60
# define PI 3.14159265358

typedef struct s_params
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			ceiling;
	int			floor;
}				t_params;

typedef struct s_file
{
	t_list		*map;
	char		**scene;
	t_params	param[1];
}				t_file;

/*Textures initialisées par/pour la mlx*/
typedef struct s_img {
	void		*no;
	void		*so;
	void		*we;
	void		*ea;
}				t_img;

/*Coordonnées du joueur & etat pressé/relaché des touches (1/0)*/
typedef struct s_player{
	int			x_pos;
	int			y_pos;
	double		dx_pos;
	double		dy_pos;
	int			up_press;
	int			dowm_press;
	int			left_press;
	int			right_press;
}				t_player;

/*Dans de nb fonctions de la mlx on ne peut passer qu'une variable en parametre : 
je passe dont t_mlx *mlx avec ses nombreux liens vers d'autres structures*/
typedef struct s_mlx
{
	void		*init_ptr; //pointeur d'initialisation de la mlx
	void		*win; //pointeur identifiant la fenetre dans laquelle on bosse
	void		*img; //pointeur de l'image sur laquelle on va bosser
	char		*addr_img; // + utile : l'adresse de l'image, permet des modifications en temps reel
	int			bits_per_pixel; //init par la mlx
	int			line_length; //init par la mlx
	int			endian; // = 0, init par la mlx
	t_img		*img_xpm;
	t_file		*file;
	t_player	player[1];
}				t_mlx;


/* --- PARSING --- */

int		parse_file(t_file *file, int ac, char **av);
int		check_params(t_file *file);

// check_walls
int		not_walled_in(t_file *file);

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
int		render_next_frame(t_mlx *mlx);

/* -- move.c -- */
int		deal_press_key(int keycode, t_mlx *mlx);
int		deal_release_key(int keycode, t_mlx *mlx);

# endif

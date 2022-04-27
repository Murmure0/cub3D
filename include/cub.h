/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/26 14:12:55 by mberthet         ###   ########.fr       */
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
# define SCALE_MAP 16 //coté en pixel des carrés de la minimap
# define SPEED 0.05 //deplacement sur la minimop
# define FOV 66 //field of view : angle sur lequel on capte les infos en jeu


typedef struct param_nb
{
	int		no;
	int		so;
	int		we;
	int		ea;
	int		c;
	int		f;
	
}				t_p_nb;

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

/*Textures initialisées par/pour la mlx : voir init.c*/
typedef struct s_img {
	void		*no;
	void		*so;
	void		*we;
	void		*ea;
}				t_img;

/*WIP CAMERA : reprise exacte des variables utilisees dans le tuto, surement certaines useless ou deja existantes*/
typedef struct s_cam
{
	double		planeX; //plane X & planeY : the camera plane of the player
	double		planeY;

	double		cameraX; //x-coordinate in camera space
	double		rayDirX;
	double		rayDirY;
	int			mapX; //which box of the map we're in
	int			mapY;
	double		sideDistX; //length of ray from current position to next x or y-side
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX; //what direction to step in x or y-direction (either +1 or -1)
	int			stepY;
	int			hit; //was there a wall hit?
	int			side; //was a NS or a EW wall hit?

	double		time; //time of current frame
	double		oldTime; //time of previous frame
}				t_cam;

/*Coordonnées du joueur & etat pressé/relaché des touches (1/0) : voir move.c*/
typedef struct s_player{
	int			x_pos;
	int			y_pos;
	double		dx_pos; //dx_pos & dy_pos : the position vector of the player
	double		dy_pos;
	double		player_dir;
	double		dirX; //dirX & dirY : the direction of the player
	double		dirY;
	int			up_press;
	int			down_press;
	int			left_press;
	int			right_press;
}				t_player;

/*Dans de nb fonctions de la mlx on ne peut passer qu'une variable en parametre : 
je passe donc t_mlx *mlx avec ses nombreux liens vers d'autres structures*/
typedef struct s_mlx
{
	void		*init_ptr; //pointeur d'initialisation de la mlx
	void		*win; //pointeur identifiant la fenetre dans laquelle on bosse
	void		*img; //pointeur sur l'image sur laquelle on a/va bosser
	char		*addr_img; // + utile : l'adresse de l'image, permet des modifications en temps reel
	int			bits_per_pixel; //init par la mlx par mlx_get_data_addr
	int			line_length; //idem
	int			endian; // = 0, idem (+info : voir big-endian et little-endian)
	t_img		*img_xpm;
	t_file		*file;
	t_player	*player;
	t_cam		*cam;
}				t_mlx;


/* --- PARSING --- */

int		parse_file(t_file *file, int ac, char **av);
int		check_params(t_file *file);

int	is_space(char c);

// check_walls
int		not_walled_in(t_file *file);

// parse_utils
int		convert_list_to_array(t_file *file);
int		check_for_newline(t_list *map);
int		parse_spaces(char *str);
int		missing_param(t_p_nb p_nb);
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

/* -- camera.c -- */
int		init_cam(t_mlx *mlx, t_file *file);

# endif

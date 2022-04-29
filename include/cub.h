/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/28 16:05:02 by mberthet         ###   ########.fr       */
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

/*Coordonnées du joueur & etat pressé/relaché des touches (1/0) : voir move.c*/
typedef struct s_player{
	int			x_pos;
	int			y_pos;
	double		dx_pos; //dx_pos & dy_pos : the position vector of the player
	double		dy_pos;
	double		player_dir;
	double		dirX; //dirX(cos(player_dir)) & dirY(sin(player_dir)) : the direction of the player
	double		dirY;
	int			up_press;
	int			down_press;
	int			left_press;
	int			right_press;
}				t_player;

/*DDA/raytracing :
reprends une partie des var de t_player pour pouvoir eventuellement 
les modifier lors des calculs du raytracing*/
typedef struct s_ray
{
	int			r_x_pos; //vPlayer : position du player au debut en int (tab de la map)
	int			r_y_pos; //vPlayer : position du player au debut en int (tab de la map)

	double		r_dx_pos; //vRaystart : position du player au debut en double (map)
	double		r_dy_pos; //vRaystart : position du player au debut en double (map)

	double		r_player_dir; //vRaydir  : dir dans laquelle le joueur regarde, en radian

	double		r_dirX; //dirX(cos(player_dir)) : the direction of the player on x axe
	double		r_dirY; // dirY(sin(player_dir)) : the direction of the player on y axe

	double		r_ray_unit_step_size_x; //position du rayon sur x durant le calcul
	double		r_ray_unit_step_size_y; //position du rayon sur y durant le calcul

	int			r_map_check_x; // reprend la pos du player/rayon initiale en int sur x (tab de la map)
	int			r_map_check_y; // reprend la pos du player/rayon initiale en int sur y (tab de la map)

	double		r_raylength_x; //stock la position actulle temporaire du rayon sur x (map)
	double		r_raylength_y; //stock la position actulle temporaire du rayon sur y (map)
	
	int			r_step_x; //stock la position actulle temporaire du rayon sur x en int (tab de la map)
	int			r_step_y; //stock la position actulle temporaire du rayon sur y en int (tab de la map)

	double		r_dist_x;
	double		r_dist_y;

	double		hit_x;
	double		hit_y;
}	t_ray;

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
	t_ray		*ray;
}				t_mlx;


/* --- PARSING --- */

int		parse_file(t_file *file, int ac, char **av);
int		check_params(t_file *file);

int	is_space(char c);
int	trim_spaces(char **str);

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
int		render_next_frame(void *mlx);

/* -- move.c -- */
int		deal_press_key(int keycode, t_mlx *mlx);
int		deal_release_key(int keycode, t_mlx *mlx);

/* -- raytracing.c -- */
int		put_ray(t_file *file, t_mlx *mlx, t_player *player);
void	put_first_ray(t_file *file, t_mlx *mlx, t_player *player, t_ray *ray);


//TESTING FCT
void	raytracing(t_player *player, t_file *file, t_mlx *mlx);

# endif

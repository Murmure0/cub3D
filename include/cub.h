/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/10 15:52:35 by mberthet         ###   ########.fr       */
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
# include <limits.h>

# define WIN_H 1080
# define WIN_W 1080
# define SCALE_MAP 16 //coté en pixel des carrés de la minimap
# define SPEED 0.05 //deplacement sur la minimap
# define FOV 66 //field of view : angle sur lequel on capte les infos en jeu
# define EST 0 //Pour les structures de chaque texture t_img en fonction de leur orientation
# define NORTH 1
# define WEST 2
# define SOUTH 3

/* --- PARSING STRUCTURES --- */
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
	t_params	param[1];
	
	char		**scene;
	int			map_h;
	int			map_w;
}				t_file;

/* -------------------------- */

/*Quatre structure img : une pour chqaue texture, variables initialisees par la minilibx*/
typedef struct s_txt 
{
	void *txt_ptr;
	char *txt_adr;
	int	w;
	int	h;
	int	bpp;
	int	len;
	int	endian;
}				t_txt;

/*Coordonnées du joueur & etat pressé/relaché des touches (1/0) : voir move.c*/
typedef struct s_player{
	int			x_pos;
	int			y_pos;
	double		dx_pos; //dx_pos & dy_pos : the position vector of the player
	double		dy_pos;
	double		player_dir;
	double		cam_dir;
	double		dirX; //dirX(cos(player_dir)) & dirY(sin(player_dir)) : the direction of the player
	double		dirY;
	double		planeX;
	double		planeY;
	int			up_press;
	int			down_press;
	int			left_press;
	int			right_press;
	int			rot_l_press;
	int			rot_r_press;
}				t_player;

/*DDA/raytracing :
reprends une partie des var de t_player pour pouvoir eventuellement 
les modifier lors des calculs du raytracing*/
typedef struct s_ray
{
	double		p_dx_pos; //vRaystart : position du player au debut en double (map)
	double		p_dy_pos; //vRaystart : position du player au debut en double (map)
	int			p_map_check_x; // reprend la pos du player/rayon initiale en int sur x (tab de la map)
	int			p_map_check_y; // reprend la pos du player/rayon initiale en int sur y (tab de la map)
	double		r_dir_x; //dirX(cos(player_dir)) : the direction of the player on x axe
	double		r_dir_y; // dirY(sin(player_dir)) : the direction of the player on y axe
	double		r_step_size_x; //position du rayon sur x durant le calcul
	double		r_step_size_y; //position du rayon sur y durant le calcul
	double		r_dist;
	int			hit;
	double		hit_x;
	double		hit_y;
	int			side;
	double		r_len_x; // longueur de l'hyp sur l'axe sur lequel on bosse
	double		r_len_y;
	int			r_step_x; // 1 / -1 : on avance avec cette dir sur X/Y
	int			r_step_y;
	double		line_len;
	int			h_wall;
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
	t_txt		*txt;
	t_file		*file;
	t_player	*player;
	t_ray		*ray;
}				t_mlx;


/* --- PARSING --- */

int		parse_file(t_file *file, int ac, char **av);
int		join_split_params(t_file *file);
int		check_params(t_file *file);
int		convert_list_to_array(t_file *file);
int		check_walls(t_file *file);

/* --- PARSING UTILS --- */

// Parse_utils
int		parse_spaces(char *str);
int		missing_param(t_p_nb p_nb);
void	convert_space_to_wall(char **map);
void	free_params(t_file *file);
void	init_map_size(t_file *file);

// Check_params_utils
void	free_param_chains(t_file *f, t_list *head);
void	param_count_init(t_p_nb *p_nb);
int		create_trgb(int t, int r, int g, int b);
int		trim_spaces(char **str);

// Lst_to_arr_utils
void	free_scene(t_file *file, int i);
int		trim_end_spaces(t_file *file);

// Check_walls_utils
int		is_space(char c);
int		check_left_wall(char *str);
int		check_right_wall(char *str);
int		is_player(char c);

// Utils
int		arraylen(char **array);
void	free_tab(char **tab);
int		fill_line(char	**str, int max_len);
int		fill_map(char **scene);
char	*trim(char *str);

/* --- MLX --- */
/* -- init.c -- */
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		launch_mlx(t_mlx *mlx, t_file *file);
int		init_mlx(t_mlx *mlx, t_file *file);
int		close_win(t_mlx *mlx, t_file *file);
void	free_all(t_file *file, t_mlx *mlx);

/* -- put_img.c -- */
void	creat_image(t_mlx *mlx, t_file *file);
void	creat_minimap(t_mlx *mlx, t_file *file);
int		render_next_frame(void *mlx);
int		put_floor(t_mlx *mlx, t_file *file, int k, double l);
int		put_ceiling(t_mlx *mlx, t_file *file, int k, double l);

/* -- move.c -- */
int		deal_press_key(int keycode, t_mlx *mlx);
int		deal_release_key(int keycode, t_mlx *mlx);
void	press_move_up(t_mlx *mlx);
void	press_move_down(t_mlx *mlx);
void	press_move_left(t_mlx *mlx);
void	press_move_right(t_mlx *mlx);
void	press_turn_left(t_mlx *mlx);
void	press_turn_right(t_mlx *mlx);

/* -- raytracing.c -- */
int		put_ray(t_file *file, t_mlx *mlx, t_player *player);
void	put_first_ray(t_file *file, t_mlx *mlx, t_player *player, t_ray *ray);

/* -- Textures -- */
int	get_texel_color(t_txt *txt, int x, int y);
// int	get_texel_color(t_txt *txt, int x, int y, int dir);


//TESTING FCT
void	raytracing(t_player *player, t_file *file, t_mlx *mlx);
//TODEL
void	print_map(char **map);

# endif

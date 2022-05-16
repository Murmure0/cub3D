/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/05/16 13:33:24 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "mlx.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> 
# include <errno.h>
# include <string.h>
# include <math.h>
# include <limits.h>

# define WIN_H 1080
# define WIN_W 1080
# define SCALE_MAP 16 // Size of side in pixels of squares of the minimap
# define SPEED 0.05 // Movement speed on minimap
# define FOV 66 // Field of view

# define WEST 2
# define NORTH 1
# define EAST 0
# define SOUTH 3

# define BLACK 0x00000000
# define WHITE 0x00FFFFFF

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

// One struct per texture type. Initialized by Minilibx
typedef struct s_txt
{
	void	*txt_ptr;
	char	*txt_adr;
	int		w;
	int		h;
	int		bpp;
	int		len;
	int		endian;
}				t_txt;

/* --- Players coordinate + key press bool variable. See move.c --- */
typedef struct s_player
{
	int			x_pos;
	int			y_pos;
	double		dx_pos;
	double		dy_pos;
	double		player_dir;
	double		cam_dir;
	int			up_press;
	int			down_press;
	int			left_press;
	int			right_press;
	int			rot_l_press;
	int			rot_r_press;
}				t_player;

/* DDA/raytracing :
copies part of t_player variables to be able to change
them up during the raytracing caluculations */
typedef struct s_ray
{
	double		p_dx_pos;
	double		p_dy_pos;
	int			p_map_check_x;
	int			p_map_check_y;
	double		r_dir_x;
	double		r_dir_y;
	double		r_step_size_x;
	double		r_step_size_y;
	double		r_dist;
	int			hit;
	double		hit_x;
	double		hit_y;
	int			side;
	double		r_len_x;
	double		r_len_y;
	int			r_step_x;
	int			r_step_y;
	double		line_len;
	int			h_wall;
}	t_ray;

/* MLX functions only accept one argument.
Thus, t_mlx stores all needed structs to work */
typedef struct s_mlx
{
	void		*init_ptr;
	void		*win;
	void		*img;
	char		*addr_img;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_txt		*txt;
	t_file		*file;
	t_player	*player;
	t_ray		*ray;
}				t_mlx;

/*******************/
/* --- PARSING --- */
/*******************/

int		parse_file(t_file *file, int ac, char **av);
int		join_split_params(t_file *file);
int		check_params(t_file *file);
int		convert_list_to_array(t_file *file);
int		check_walls(t_file *file);

/* --- PARSING UTILS --- */

/* -- parse_utils.c -- */
int		parse_spaces(char *str);
int		missing_param(t_p_nb p_nb);
void	convert_space_to_wall(char **map);
void	free_params(t_file *file);
void	init_map_size(t_file *file);

/* -- check_params_utils.c -- */
void	free_param_chains(t_file *f, t_list *head);
void	param_count_init(t_p_nb *p_nb);
int		create_trgb(int t, int r, int g, int b);
int		trim_spaces(char **str);

/* -- lst_to_arr_utils.c -- */
void	free_scene(t_file *file, int i);
int		trim_end_spaces(t_file *file);

/* -- check_walls_utils.c -- */
int		is_space(char c);
int		check_left_wall(char *str);
int		check_right_wall(char *str);
int		is_player(char c);

/* -- Utils.c -- */
int		arraylen(char **array);
void	free_tab(char **tab);
int		fill_line(char	**str, int max_len);
int		fill_map(char **scene);
char	*trim(char *str);

/***************/
/* --- MLX --- */
/***************/

/* -- mlx_init_structs.c -- */
void	init_player(t_mlx *mlx, t_file *file);
int		init_texture(t_mlx *mlx, t_file *file);

/* -- mlx_launch.c -- */
void	free_all(t_mlx *mlx);
int		close_win(t_mlx *mlx);
int		init_mlx(t_mlx *mlx, t_file *file);
int		launch_mlx(t_mlx *mlx, t_file *file);

/* -- move_dir.c -- */
int		wall_collision(t_mlx *mlx, double px, double py);
void	press_move_up(t_mlx *mlx);
void	press_move_down(t_mlx *mlx);
void	press_move_left(t_mlx *mlx);
void	press_move_right(t_mlx *mlx);

/* -- move_rotate.c -- */
void	press_turn_left(t_mlx *mlx);
void	press_turn_right(t_mlx *mlx);
int		deal_press_key(int keycode, t_mlx *mlx);
int		deal_release_key(int keycode, t_mlx *mlx);

/* -- raytracing_dda.c -- */
void	put_first_ray(t_file *file, t_mlx *mlx, t_player *player, t_ray *ray);

/* -- raytracing_wall.c -- */
void	draw_col(t_mlx *mlx, t_ray *ray, int x);
void	wall_line_len(t_ray *ray, double cam_angle);

/* -- render_new_img.c -- */
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	creat_game_image(t_mlx *mlx, t_file *file);
void	creat_image(t_mlx *mlx, t_file *file);

/* -- render_nxt_img.c -- */
void	update_player_pos(t_mlx *mlx);
int		render_next_frame(void *mlx);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/15 18:48:47 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define WIN_H 1080
# define WIN_W 1920

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

typedef struct s_mlx
{
	void	*init_ptr;
	void	*win;
	void	*img;
	char	*addr_img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}	t_mlx;
/* --- PARSING --- */

int parse_file(t_file *file, int ac, char **av);

// check_walls
int	not_walled_in(t_file *file);

// parse_utils
int	convert_list_to_array(t_file *file);
int	check_for_newline(t_list *map);
int	parse_spaces(char *str);
int	missing_param(t_params *param);
void	free_param_chains(t_file *f, t_list *head);

/* --- MLX --- */
/* -- init.c -- */
int launch_mlx(t_mlx *mlx, t_file *file);
int init_mlx(t_mlx *mlx, t_file *file);
int	deal_key(int keycode, t_mlx *mlx, t_file *file);
int	close_win(t_mlx *mlx, t_file *file);

/* -- put_img.c -- */
void creat_image(t_mlx *mlx, t_file *file);

# endif

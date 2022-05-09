/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:15:07 by mberthet          #+#    #+#             */
/*   Updated: 2021/12/10 11:17:23 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BLOCK_SIZE
#  define BLOCK_SIZE 32
# endif

typedef struct s_maillon{
	char				*map_line;
	struct s_maillon	*next;
}			t_maillon;

typedef struct s_stuff{
	int	x_pos;
	int	y_pos;
}			t_stuff;

typedef struct s_map{
	int		pars_height;
	int		pars_width;
	char	**pars_map;
	int		nb_item;
	char	*counter;
}			t_map;

typedef struct s_img {
	void	*item;
	void	*wall;
	void	*floor;
	void	*charac_up;
	void	*charac_down;
	void	*charac_right;
	void	*charac_left;
	void	*exit;
}			t_img;

typedef struct s_param {
	int		z;
	int		put_p;
	void	*mlx_ptr;
	void	*mlx_win;
	t_img	*img;
	t_map	*map;
	t_stuff	*rabbit;
}			t_param;

char		*get_next_line(int fd);

				/* ---INIT--- */
int			initialize_img(t_img *init_img, void *mlx_ptr);
void		fill_map(t_map map, t_param param_mlx, t_img init_img);
void		put_stuff_map(t_map map, t_param param_mlx, t_img init_img);
int			find_rabbit(t_param param_mlx, t_stuff *rabbit);

				/* ---PARS--- */
char		**read_map(int argc, char **argv, t_map *map);

				/* ---UTILS--- */
int			ft_strlen(char *str);
void		ft_putnbr(int n);
char		*ft_itoa(int n);

				/* ---LST_BASICS--- */
t_maillon	*new_maillon(char *line);
int			ft_lstclear_empty(t_maillon *lst);
void		ft_lstclear(t_maillon *lst);
int			ft_lstsize(t_maillon *lst);
void		free_pars_map(t_map map);

				/* ---CHECK--- */
int			valid_map(char **pars_map, t_map map);

				/* ---CHECK_TWO--- */
int			check_arg(int argc, char **argv);
int			check_mini_map(int fd, t_map *map, t_maillon *lst_gnl_map);
void		*wr_err_empt(void);
void		*wr_err_size(void);
int			find_stuff(char **pars_map, char stuff, t_map map);

				/* ---MOVE--- */
int			close_win(t_param *param_mlx);
int			deal_key(int keycode, t_param *param_mlx);

				/* ---MOVE RL--- */
int			move_right(t_param *param_mlx, t_map *map, t_stuff *rabbit,
				t_img *img);
int			move_left(t_param *param_mlx, t_map *map, t_stuff *rabbit,
				t_img *img);

				/* ---MOVE UD--- */
int			move_up(t_param *param_mlx, t_map *map, t_stuff *rabbit,
				t_img *img);
int			move_down(t_param *param_mlx, t_map *map, t_stuff *rabbit,
				t_img *img);

#endif

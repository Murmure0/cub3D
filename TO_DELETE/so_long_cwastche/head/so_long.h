/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:21:18 by cwastche          #+#    #+#             */
/*   Updated: 2022/02/04 09:19:32 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <X11/Xlib.h>
# include <X11/keysymdef.h>

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# define WALL "img/wall.xpm"
# define PLAYER "img/player.xpm"
# define COLLECT "img/collectible.xpm"
# define EXIT "img/exit.xpm"
# define FLOOR "img/floor.xpm"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;

	char	**map;
	int		player_x;
	int		player_y;
	int		moves;

	int		map_h;
	int		map_w;

	int		p;
	int		c;
	int		e;
}	t_data;

typedef struct s_asset
{
	int		h;
	int		w;
}	t_asset;

// src
void	map_check(t_data *var);
char	*map_read(char *map_path);
int		generate_map(t_data *var);

// moves
int		move_up(t_data *var);
int		move_down(t_data *var);
int		move_left(t_data *var);
int		move_right(t_data *var);

// utils
void	error(char	*msg, t_data *var);
int		close_win(t_data *var);
int		error_win(t_data *var, int n);
void	map_free(char **map);
void	map_size(t_data *var);

#endif

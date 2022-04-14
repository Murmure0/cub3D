/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/14 17:53:00 by mberthet         ###   ########.fr       */
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

int 		parse_file(t_file *file, int ac, char **av);

/* --- MLX --- */

int init_mlx(t_mlx *mlx, t_file *file);
int	deal_key(int keycode, t_mlx *mlx, t_file *file);
int	close_win(t_mlx *mlx);

# endif
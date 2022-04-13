/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/13 13:17:25 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
//# include Minilibx lib

typedef struct s_wall_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_wall_t;

typedef struct s_input
{
	char		**map;

	int			ceiling; //maybe struct aswell
	int			floor;
	
	t_wall_t 	wall_texture;
}	t_input;

typedef struct s_file
{
	t_input	input;
}	t_file;

/* --- Parsing --- */

int parse_file(t_file *file, int ac, char **av);

# endif
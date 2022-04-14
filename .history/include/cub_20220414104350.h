/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:20:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/04/13 16:50:33 by mberthet         ###   ########.fr       */
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
//# include Minilibx lib

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
	t_params param;
}				t_file;

/* --- PARSING --- */

int 		parse_file(t_file *file, int ac, char **av);

// --- UTILS_LST ---

// t_maillon	*new_maillon(char *line);
// int			ft_lstclear_empty(t_maillon *lst);
// void		ft_lstclear(t_maillon *lst);

char		*get_next_line(int fd);

# endif
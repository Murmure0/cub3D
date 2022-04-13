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

#include <stdio.h> 
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef CUB_H
# define CUB_H

typedef struct s_maillon{
	char				*line;
	struct s_maillon	*next;
}			t_maillon;

typedef struct s_file
{
	t_maillon *param_map; //stock les quatre path pour les textures & les couleurs sol/plafond
	t_maillon *map; //stock la map
}	t_file;


/* --- PARSING --- */

int 		parse_file(t_file *file, int ac, char **av);

/* --- UTILS ---*/
/* --- UTILS_STR --- */
int 		ft_strlen(char *str);
int			ft_strncmp(const char *str1, const char *str2, size_t n);

/* --- UTILS_LST --- */

t_maillon	*new_maillon(char *line);
int			ft_lstclear_empty(t_maillon *lst);
void		ft_lstclear(t_maillon *lst);
int			ft_lstsize(t_maillon *lst);

char		*get_next_line(int fd);

# endif
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 11:02:35 by mberthet          #+#    #+#              #
#    Updated: 2021/12/10 12:00:03 by mberthet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I mlx

FLAGMLX = -L. -lmlx -framework OpenGL -framework AppKit

SHARED = lst_basics.c \
			pars_map.c \
			check.c \
			check_two.c \
			./GNL/get_next_line.c \
			utils.c


MAIN = main.c \
		init.c \
		move.c \
		move_r_l.c \
		move_u_d.c 

BONUS = main_bonus.c \
		init_bonus.c \
		move_bonus.c \
		move_r_l_bonus.c \
		move_u_d_bonus.c 

SOURCES = $(SHARED) $(MAIN)

BSOURCES = $(SHARED) $(BONUS)

HEADER = so_long.h

OBJECTS = $(SOURCES:.c=.o)

BOBJECTS = $(BSOURCES:.c=.o)

all : $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
			$(CC) $(FLAGMLX) $(CFLAGS) $(OBJECTS) -o $(NAME)

bonus: ${BOBJECTS} $(HEADER)
			@$(CC) $(FLAGMLX) $(BCFLAGS) $(BOBJECTS) -o $(NAME)

clean:
	/bin/rm -f $(OBJECTS) $(BOBJECTS) all
	
fclean: clean
	/bin/rm -f $(NAME) all
	
re: fclean all

.PHONY: clean fclean re all bonus

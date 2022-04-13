# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 11:55:53 by mberthet          #+#    #+#              #
#    Updated: 2022/04/13 16:53:46 by mberthet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc

RM = rm -rf

CFLAGS =	-Wall -Wextra -Werror -g -I mlx

# CFLAGS += -fsanitize=address

INCLUDE =	-L. -lmlx -framework OpenGL -framework AppKit

SOURCES =	srcs/main.c	\
			srcs/parsing/parse_file.c	\
			srcs/utils/utils_str.c	\
			srcs/utils/utils_lst.c	\
			srcs/utils/get_next_line.c	\

OBJECTS =	$(SOURCES:.c=.o)

all :		$(NAME)

$(NAME):	$(OBJECTS)
		@$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) -o $(NAME) && make clean
		@echo "[\033[32m$(NAME) ready to use\033[0m]"

clean:
	@$(RM) $(OBJECTS)
	
fclean: clean
	@$(RM) $(NAME)
	
re: fclean all

.PHONY: clean fclean re all
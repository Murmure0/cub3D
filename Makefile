# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 11:55:53 by mberthet          #+#    #+#              #
#    Updated: 2022/04/13 13:16:14 by mberthet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d

CC = gcc

CFLAGS =	-Wall -Wextra -Werror

#INCLUDE =	-lmlx -framework OpenGL -framework AppKit

# CFLAGS += -fsanitize=address

SOURCES =	srcs/main.c	\
			srcs/parsing/parse_file.c	\

RM = rm -rf

OBJECTS =	$(SOURCES:.c=.o)

all :		$(NAME)

$(NAME):	$(OBJECTS)
		@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) && make clean
#ajouter $(INCLUDE) pour la mlx
		@echo "[\033[32m$(NAME) ready to use\033[0m]"


clean:
	@$(RM) $(OBJECTS)
	
fclean: clean
	@$(RM) $(NAME)
	
re: fclean all

.PHONY: clean fclean re all
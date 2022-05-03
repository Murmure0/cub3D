# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 11:55:53 by mberthet          #+#    #+#              #
#    Updated: 2022/05/03 10:39:36 by mberthet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc

RM = rm -rf

CFLAGS =	-Wall -Wextra -Werror -g -I mlx

CFLAGS += -fsanitize=address -static-libsan -g

INC		= 	-I./include/

INCLUDE =	-L. -lmlx -framework OpenGL -framework AppKit

SOURCES =	srcs/main.c	\
			srcs/parsing/check_params_utils.c \
			srcs/parsing/check_params.c \
			srcs/parsing/check_walls_utils.c \
			srcs/parsing/check_walls.c \
			srcs/parsing/convert_list_to_array.c \
			srcs/parsing/join_split_params.c \
			srcs/parsing/parse_file.c	\
			srcs/parsing/parse_utils.c	\
			srcs/parsing/trim_map_into_shape.c \
			srcs/mlx/init.c	\
			srcs/mlx/put_img.c	\
			srcs/mlx/move.c	\
			gnl/get_next_line.c	\
			srcs/mlx/raytracing_lode_tuto.c	\
			#srcs/mlx/raytracing.c	\

OBJ_DIR =	obj
OBJECTS =	$(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

all :		$(NAME)

$(NAME):	$(OBJECTS)
		@$(MAKE) -C ./libft
		@$(CC) $(INCLUDE) $(CFLAGS) $(OBJECTS) ./libft/libft.a -o $(NAME)

		@echo "[\033[32m$(NAME) ready to use\033[0m]"

$(OBJ_DIR)/%.o : %.c
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/srcs $(OBJ_DIR)/srcs/utils $(OBJ_DIR)/srcs/parsing $(OBJ_DIR)/gnl $(OBJ_DIR)/srcs/mlx
	$(CC) $(CFLAGS) -c $(INC) $< -o $@

clean:
	$(MAKE) -C ./libft fclean
	@$(RM) $(OBJECTS) $(OBJ_DIR)
	
fclean: clean
	@$(RM) $(NAME)
	
re: fclean all

.PHONY: clean fclean re all
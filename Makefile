# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 11:55:53 by mberthet          #+#    #+#              #
#    Updated: 2022/05/18 10:25:42 by mberthet         ###   ########.fr        #
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
			srcs/parsing/lst_to_arr_utils.c \
			srcs/parsing/parse_file.c	\
			srcs/parsing/parse_file_init.c	\
			srcs/parsing/parse_utils.c	\
			srcs/parsing/utils.c \
			srcs/mlx/mlx_init_structs.c	\
			srcs/mlx/mlx_launch.c	\
			srcs/mlx/move_dir.c	\
			srcs/mlx/move_rotate.c	\
			gnl/get_next_line.c	\
			srcs/mlx/raytracing_dda.c	\
			srcs/mlx/raytracing_wall.c	\
			srcs/mlx/render_new_img.c	\
			srcs/mlx/render_nxt_img.c	\


OBJ_DIR =	obj
OBJECTS =	$(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

all :		$(NAME)

$(NAME):	$(OBJECTS)
		@echo "[\033[32m$(NAME) compiling ...\033[0m]"
		@$(MAKE) -C ./libft
		@$(CC) $(INCLUDE) $(CFLAGS) $(OBJECTS) ./libft/libft.a -o $(NAME)

		@echo "[\033[32m$(NAME) ready to use\033[0m]"

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/srcs $(OBJ_DIR)/srcs/parsing $(OBJ_DIR)/gnl $(OBJ_DIR)/srcs/mlx
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@

clean:
	@$(MAKE) -C ./libft fclean
	@$(RM) $(OBJECTS) $(OBJ_DIR)
	@echo "[\033[32m$(NAME) files cleaned !\033[0m]"
	
fclean: clean
	@$(RM) $(NAME)
	@echo "[\033[32m$(NAME) files fcleaned !\033[0m]"
	
re: fclean all

.PHONY: clean fclean re all
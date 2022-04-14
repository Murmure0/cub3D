# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwastche </var/mail/cwastche>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/28 13:37:15 by cwastche          #+#    #+#              #
#    Updated: 2021/08/01 14:25:39 by cwastche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	   ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	   ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	   ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	   ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	   ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

BSRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
		ft_lstsize.c

DIR_OBJ = obj
OBJS = $(addprefix $(DIR_OBJ)/,$(SRCS:.c=.o))
BOBJS = $(addprefix $(DIR_OBJ)/,$(BSRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = libft.a
HEAD = libft.h
AR = ar rc

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $@ $^

bonus : $(BOBJS)
	$(AR) $(NAME) $^

$(DIR_OBJ)/%.o : %.c $(HEAD)
	@mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS) $(BOBJS) $(DIR_OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 11:07:37 by gcollet           #+#    #+#              #
#    Updated: 2025/10/22 12:58:27 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = srcs/utils.c srcs/pipex_bonus.c srcs/utils_bonus.c\
	srcs/ft_split.c srcs/ft_strjoin.c srcs/ft_strlen.c srcs/ft_strncmp.c\
	srcs/ft_strnstr.c srcs/ft_strlcpy.c srcs/ft_putstr_fd.c\
	srcs/ft_putchar_fd.c\
	  
OBJ = $(SRC:.c=.o)

INCLUDE = includes/pipex.h

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
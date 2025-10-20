# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 09:24:28 by atabarea          #+#    #+#              #
#    Updated: 2025/10/20 14:28:45 by atabarea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = src/pipex.c src/error.c src/freer.c src/ft_putchar_fd.c\
	src/ft_split.c src/ft_putstr_fd.c src/ft_putendl_fd.c src/ft_strcmp.c\
	src/ft_strlen.c src/get_path.c src/open_file.c src/error_cmd.c\
	src/ft_strjoin.c src/ft_substr.c src/ft_strchr.c src/ft_strdup.c\
	src/fd_closer.c src/numoffds.c

OBJ = $(SRC:.c=.o)

INCLUDE = pipex.h

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
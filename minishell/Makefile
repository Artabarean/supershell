# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 0025/11/14 10:40:04 by tabarea           #+#    #+#              #
#    Updated: 2026/01/26 15:06:38 by atabarea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC	  = cc
CFLAGS   = -Wall -Wextra -Werror -Wuninitialized

LFT	 = ../execution/libft/libft.a
INC	 = -I ../execution/libft
LIB	 = -L ../execution/libft -lft -lreadline

SRC	 =	main.c \
		enviroment.c \
		lexer.c \
		lexer_utils.c \
		lexer_utils2.c \
		init.c \
		utils.c \
		parser.c \
		parser_utils.c \
		clean.c \
		signal.c \
		input.c \
		execute_.c \
		executer.c \
		pipex.c \
		utils_pipex.c \
		utils-executor.c \
		debugging.c \
		find_path.c \
		selectprocess.c \
		echo.c \
		pwd.c \
		env.c \
		cd.c \
		unset.c \
		builtins.c \
		find_inorout.c \
		exit_builtin.c \
		here_doc.c \
		here_doc_check.c \
		check_error.c \
		utils_cd.c \
		utils_export.c \
		export.c \
		expand.c \
		expand_utils.c \
		printnofile.c \
		is_single_builtin.c 

OBJS	= $(patsubst %.c,obj/%.o,$(SRC))

all: $(LFT) obj $(NAME)

$(NAME): $(OBJS)
	@echo "$(CC) $(CFLAGS) -o $@"
	@printf "%s\n" $(OBJS)
	@echo "$(LIB)"
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIB) 

$(LFT):
	@echo " [ .. ] | Compiling libft.."
	@make -s -C ../execution/libft
	@echo " [ OK ] | Libft ready!"

obj:
	@mkdir -p obj

obj/%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make -s clean -C ../execution/libft
	@rm -rf $(OBJS) obj
	@echo "object files removed."

fclean: clean
	@make -s fclean -C ../execution/libft
	@rm -rf $(NAME)
	@echo "binary file removed."

re: fclean all

.PHONY: all clean fclean re

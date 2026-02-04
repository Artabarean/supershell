# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 0025/11/14 10:40:04 by tabarea           #+#    #+#              #
#    Updated: 2026/02/04 11:09:15 by atabarea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc
CFLAGS  = -Wall -Wextra -Werror -Wuninitialized -g

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
LIBFT_DIR = $(INC_DIR)/libft

INC	 = -I$(INC_DIR) -I$(LIBFT_DIR)/inc
LIBS = $(LIBFT_DIR)/libft.a -lreadline

SRC	 =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/utils/enviroment.c \
		$(SRC_DIR)/parser/lexer.c \
		$(SRC_DIR)/parser/lexer_utils.c \
		$(SRC_DIR)/parser/lexer_utils2.c \
		$(SRC_DIR)/parser/init.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/parser/parser.c \
		$(SRC_DIR)/parser/parser_utils.c \
		$(SRC_DIR)/utils/clean.c \
		$(SRC_DIR)/utils/signal.c \
		$(SRC_DIR)/parser/input.c \
		$(SRC_DIR)/exec/execute_.c \
		$(SRC_DIR)/exec/executer.c \
		$(SRC_DIR)/exec/pipex.c \
		$(SRC_DIR)/exec/utils_pipex.c \
		$(SRC_DIR)/exec/utils-executor.c \
		$(SRC_DIR)/debugging.c \
		$(SRC_DIR)/exec/find_path.c \
		$(SRC_DIR)/exec/selectprocess.c \
		$(SRC_DIR)/builtins/echo.c \
		$(SRC_DIR)/builtins/pwd.c \
		$(SRC_DIR)/utils/env.c \
		$(SRC_DIR)/builtins/cd.c \
		$(SRC_DIR)/builtins/unset.c \
		$(SRC_DIR)/builtins/builtins.c \
		$(SRC_DIR)/exec/find_inorout.c \
		$(SRC_DIR)/builtins/exit_builtin.c \
		$(SRC_DIR)/exec/here_doc.c \
		$(SRC_DIR)/exec/here_doc_check.c \
		$(SRC_DIR)/utils/check_error.c \
		$(SRC_DIR)/builtins/utils_cd.c \
		$(SRC_DIR)/builtins/utils_export.c \
		$(SRC_DIR)/builtins/export.c \
		$(SRC_DIR)/parser/expand.c \
		$(SRC_DIR)/parser/expand_utils.c \
		$(SRC_DIR)/parser/expand_utils2.c \
		$(SRC_DIR)/builtins/is_single_builtin.c \
		$(SRC_DIR)/utils/error_checks.c \
		$(SRC_DIR)/exec/handle_finder.c \
		$(SRC_DIR)/exec/utils_pipex2.c \
		$(SRC_DIR)/exec/check_paths.c \
		$(SRC_DIR)/builtins/utils_export2.c \
		$(SRC_DIR)/utils/cmd_isdir.c  

OBJS	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h
	@mkdir -p $(dir $@)
	@echo "MINISHELL Compiling:$(END) $(notdir $<)"
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	@echo " [ .. ] | Compiling libft.."
	@make -sC $(LIBFT_DIR)
	@echo " [ OK ] | Libft ready!"
	@$(CC) $(OBJS) $(CFLAGS) $(INC) $(LIBS) -g -o $@
	@echo "\n$[Compiled $ $@ $ successfully]\n"

clean:
	@make -s clean -C ./inc/libft
	@rm -rf $(OBJ_DIR)
	@echo "object files removed."

fclean: clean
	@make -s fclean -C ./inc/libft
	@rm -rf $(NAME)
	@echo "binary file removed."

re: fclean all

.PHONY: all clean fclean re

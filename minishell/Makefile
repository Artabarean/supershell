NAME	= minishell
CC	  = cc -lreadline
CFLAGS   = -Wall -Wextra -Werror

LFT	 = ../execution/libft/libft.a
INC	 = -I ../execution/libft
LIB	 = -L ../execution/libft -lft -lreadline

SRC	 =	main.c \
		enviroment.c \
		lexer.c \
		lexer_utils.c \
		init.c \
		utils.c \
		parser.c \
		parser_utils.c \
		clean.c \
		signal.c \
		input.c \
		builtins.c \
		execute_.c \
		executer.c \
		pipex.c \
		utils_pipex.c \
		utils-executor.c \
		debugging.c \
		find_path.c \
		selectprocess.c \

OBJS	= $(patsubst %.c,obj/%.o,$(SRC))

all: $(LFT) obj $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(LFT):
	@echo " [ .. ] | Compiling libft.."
	@make -s -C ../execution/libft
	@echo " [ OK ] | Libft ready!"

obj:
	@mkdir -p obj

obj/%.o: %.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

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
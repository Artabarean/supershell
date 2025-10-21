NAME	= minishell
CC	  = cc -lreadline
CFLAGS   = -Wall -Wextra -Werror

LFT	 = libft/libft.a
INC	 = -I ./libft
LIB	 = -L ./libft -lft -lreadline

SRC	 =	main.c \
		enviroment.c \
		lexer.c \
		lexer_utils.c \

OBJS	= $(patsubst %.c,obj/%.o,$(SRC))

ll: $(LFT) obj $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(LFT):
	@echo " [ .. ] | Compiling libft.."
	@make -s -C libft
	@echo " [ OK ] | Libft ready!"

obj:
	@mkdir -p obj

obj/%.o: %.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@make -s clean -C libft
	@rm -rf $(OBJS) obj
	@echo "object files removed."

fclean: clean
	@make -s fclean -C libft
	@rm -rf $(NAME)
	@echo "binary file removed."

re: fclean all

.PHONY: all clean fclean re
NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra 
RM = rm -f
LIBFT_NAME = libft/libft.a
LIBFT = make -C ./libft
LIBFT_CLEAN = make clean -C ./libft
LIBFT_FCLEAN = make fclean -C ./libft
LINK = -lreadline -L$(HOME)/.brew/opt/readline/lib 
COMPILE = -I/$(HOME)/.brew/opt/readline/include -g
OBJ = $(SRC:.c=.o)

.SILENT: $(OBJ)

SRC = src/builtins.c \
			src/ft_tokeniz.c \
			src/ft_pipe.c \
			src/utils2.c \
			src/echo_pars.c \
			src/ft_exec.c \
			src/ft_export.c \
			src/utils.c \
			src/free_and_exit.c \
			src/main.c \
			src/parsing.c \
			src/all_redirect/redirect.c \
			src/all_redirect/redirect_one.c \
			src/all_redirect/redirect_two.c \
			src/all_redirect/redirect_tree.c \
			src/all_redirect/redirect_four.c \

all: $(NAME)

$(NAME): $(OBJ)
			$(LIBFT) && $(CC) $(FLAGS) $(LINK) $(OBJ) $(LIBFT_NAME) -o $(NAME)
%.o: %.c
			$(CC) $(FLAGS) $(COMPILE) -c $< -o $@

clean: 
			@$(RM) $(OBJ) && $(LIBFT_CLEAN)

fclean: clean
			@$(RM) $(NAME) && $(LIBFT_FCLEAN)

re: fclean all

.PHONY: all clean fclean re

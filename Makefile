SRCS =	main.c \
		builtin/builtin.c builtin/cd_builtin.c builtin/cd_builtin_utils.c	\
		builtin/echo_builtin.c builtin/exit_builtin.c builtin/signals.c		\
		builtin/export_builtin.c builtin/export_builtin_utils.c				\
		builtin/unset_builtin.c												\
		exec/exec.c exec/pipes.c exec/redirect.c exec/redirect_utils.c		\
		exec/utils.c exec/exec_utils.c										\
		lexer/lexer.c lexer/lexer_utils.c lexer/lexer_utils_2.c				\
		lexer/lexer_str.c lexer/check_syntax.c 						 		\
		utils/ft_nbr.c utils/ft_split.c utils/ft_str_1.c utils/ft_str_2.c	\
		utils/ft_str_3.c utils/lst_all.c

CC = @gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
RM = @rm -rf

OBJS = $(SRCS:.c=.o)

READLINE = readline

all: $(READLINE) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install


$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

fclean: clean
	$(RM) $(NAME)
	@rm -rf readline-8.2 readline-8.2.tar.gz

clean:
	$(RM) $(OBJS)

re: fclean all

.PHONY: all fclean clean re
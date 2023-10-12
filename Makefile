SRCS =	main.c \
		builtin/builtin.c builtin/cd_builtin.c builtin/cd_builtin_utils.c	\
		builtin/echo_builtin.c builtin/exit_builtin.c builtin/signals.c		\
		builtin/export_builtin.c builtin/export_builtin_utils.c				\
		builtin/unset_builtin.c												\
		exec/exec.c exec/pipes.c exec/redirect.c exec/redirect_utils.c		\
		exec/utils.c														\
		lexer/lexer.c lexer/lexer_utils.c lexer/lexer_utils_2.c				\
		lexer/lexer_str.c lexer/check_syntax.c 						 		\
		utils/ft_nbr.c utils/ft_split.c utils/ft_str_1.c utils/ft_str_2.c	\
		utils/ft_str_3.c utils/lst_all.c

CC = @gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
RM = @rm -rf

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS)

re: fclean all

.PHONY: all fclean clean re

SRCS = main.c utils/lst_all.c utils/ft_split.c utils/ft_str.c lexer/lexer.c \
		utils/ft_str_clone.c lexer/lexer_utils.c lexer/lexer_str.c
OBJS = $(SRCS:.c=.o)
CC = @gcc

CFLAGS = -g
LFLAGS = -lreadline
RM = @rm -rf
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS)

re: fclean all

.PHONY: all fclean clean re

# gcc -lreadline -g -fsanitize=address lexer/*.c utils/*.c main.c
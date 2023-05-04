CC			=	gcc -g3 -fsanitize=address
# CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
LDFLAGS		=	-lreadline
RM			=	/bin/rm -f
NAME		=	minishell
INCLUDES	=	./includes


SRCS		=	main.c \
				builtin/ft_echo.c \
				execute/execute.c \
				execute/utils_exe.c \
				parse/parsing.c \
				parse/path.c \
				tools/calloc.c \
				tools/ft_replace.c \
				tools/ft_split.c \
				tools/helpers.c \
				tools/linked_list.c \
				tools/util.c \

OBJS		=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

norm :
	@norminette -R CheckForbiddenSourceHeader $(SRCS) headers/

r:
	make re && clear && ./minishell
# --track-fds=yes --tool=memcheck --leak-check=full --show-leak-kinds=all

v:
	make re && clear && valgrind --leak-check=full --show-leak-kinds=all --suppressions=.ignore_readline --trace-children=yes ./minishell

.PHONY: all re clean fclean m

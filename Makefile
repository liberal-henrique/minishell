# CC			=	cc -g -fsanitize=address
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
LDFLAGS		=	-lreadline
RM			=	/bin/rm -f
NAME		=	minishell
INCLUDES	=	./includes


SRCS		=	main.c \
				builtin/ft_cd.c \
				builtin/ft_echo.c \
				builtin/ft_env.c \
				builtin/export_utils.c \
				builtin/ft_export.c \
				builtin/ft_pwd.c \
				builtin/ft_unset.c \
				execute/execute_redirections.c \
				execute/execute.c \
				execute/utils_exe.c \
				parse/expander.c \
				parse/parsing.c \
				parse/path.c \
				tools/calloc.c \
				tools/comands.c \
				tools/ft_substring.c \
				tools/ft_replace.c \
				tools/ft_split.c \
				tools/helpers.c \
				tools/linked_list.c \
				tools/tokens.c \
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
	make re && clear && valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=.ignore_readline --trace-children=yes ./minishell

.PHONY: all re clean fclean m

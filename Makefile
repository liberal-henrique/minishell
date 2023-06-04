CC			=	cc -fsanitize=address
# CC			=	cc
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
				builtin/export_utils2.c \
				builtin/ft_export.c \
				builtin/ft_export2.c \
				builtin/ft_pwd.c \
				builtin/ft_unset.c \
				builtin/ft_exit.c \
				builtin/ft_exit2.c \
				execute/execute_redirections.c \
				execute/execute_redirections2.c \
				execute/execute.c \
				execute/execute2.c \
				execute/utils_exe.c \
				execute/cleanall.c \
				parse/expander.c \
				parse/expander2.c \
				parse/parsing.c \
				parse/parsing2.c \
				parse/path.c \
				tools/calloc.c \
				tools/comands.c \
				tools/comands2.c \
				tools/ft_substring.c \
				tools/ft_replace.c \
				tools/ft_split.c \
				tools/helpers.c \
				tools/helpers2.c \
				tools/linked_list.c \
				tools/tokens.c \
				tools/util.c \
				tools/util2.c \

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

a:	make re && clear

r:
	make re && clear && ./minishell

t:
	make re && clear && cd minishell_tester && ./tester
# --track-fds=yes --tool=memcheck --leak-check=full --show-leak-kinds=all

v:
	make re && clear && valgrind -s --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=.ignore_readline --trace-children=yes ./minishell

.PHONY: all re clean fclean m

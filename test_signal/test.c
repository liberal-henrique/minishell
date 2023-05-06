#include<signal.h>
#include<stdarg.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include<readline/readline.h>
#include<readline/history.h>

void	sighandler()
{
	printf("\n");
	rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 1); // Clear the previous text
    rl_redisplay();
}

int	main(int ac, char **av)
{
	char	*line;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("Minishell$ ");
		add_history(line);
		if (!line)
			exit(0);
		free(line);
	}
	return (0);
}

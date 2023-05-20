
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include<readline/readline.h>
#include<readline/history.h>

// Signal libraries
#include<signal.h>
#include<stdarg.h>
#include<sys/types.h>

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) ac;
	(void) av;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("Minishell$ ");
		if (!line)
		{
			// Caso eu tente realizar a limpeza da memoria
			//eu causarei um segmentation fault;
			// deallocate(g_terminal.begin);
			exit(0);
		}
		add_history(line);
		free(line);
	}
	return (0);
}
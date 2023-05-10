/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:55:52 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/10 18:09:13 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_terminal	g_terminal;

void	sighandler()
{
	printf("\n");
	rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 1); // Clear the previous text
    rl_redisplay(); //update the display of the current line on the terminal
}

int	main(int ac, char **av, char **env)
{
	char	*line;


	clone_env(env);
	(void) ac;
	(void) av;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		// int i = -1;
		// while (g_terminal.env[++i])
		// 	printf("AUI: %s\n", g_terminal.env[i]);
		line = readline("Minishell$ ");
		if (!line)
		{
			// Caso eu tente realizar a limpeza da memoria
			//eu causarei um segmentation fault;
			// deallocate(g_terminal.begin);
			exit(0);
		}
		add_history(line);
		tokens(line);
		free(line);
	}
	return (0);
}

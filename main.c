/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:55:52 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/18 13:57:11 by lliberal         ###   ########.fr       */
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

	(void) ac;
	(void) av;
	g_terminal.env = clone_env(env);
	g_terminal.expo = create_expo(env);
	signal(SIGINT, sighandler);
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
		ft_phrases(line);
		free(line);
	}
	return (0);
}

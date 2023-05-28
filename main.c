/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:55:52 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/28 23:01:48 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_terminal	g_terminal;

void	sighandler()
{
	printf("\n");
	rl_on_new_line(); //Regenerate the prompt on a newline
	rl_replace_line("", 1);// Clear the previous text
	rl_redisplay(); //update the display of the current line on the terminal
	//printf("\n");
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) ac;
	(void) av;
	g_terminal.env = clone_env(env);
	g_terminal.expo = create_expo(env);
	/* if (ft_strlen_2d(env) != 0)
	{
		g_terminal.env = clone_env(env);
		g_terminal.expo = create_expo(env);
	}
	else
	{
		g_terminal.env = NULL;
		g_terminal.expo = NULL;
	} */
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	while (1)
	{
		line = readline("Minishell$ ");
		if (!line)
		{
			cleanall(g_terminal.begin);
			printf("exit\n");
			exit(STATUS_SUCCESS);
		}
		if (line[0] == 0)
			exit(g_terminal.status);
		if (line && line[0] != 0)
		{
			add_history(line);
			ft_phrases(line);
			free(line);
		}
	}
	return (0);
}

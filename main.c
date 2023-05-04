/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:55:52 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/04 16:51:33 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_terminal	g_terminal;

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) ac;
	(void) av;
	g_terminal.env = env;
	while (1)
	{
		line = readline("Minishell$ ");
		add_history(line);
		tokens(line);
		free(line);
	}
	return (0);
}

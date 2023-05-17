/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:43:37 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/17 22:05:57 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_2d(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

int	ft_strlen_2d(char **a)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
		i++;
	return (i);
}

char	**synchronize_env(char **env, char *cmd)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = increase_env(env);
	while (new_env[++i])
		new_env[i] = new_env[i];
	new_env[i] = ft_strdup(cmd);
	free(env);
	return (new_env);
}

int	execute_env(t_cmd *cmd)
{
	int	i;

	i = -1;
	(void) cmd;
	while (g_terminal.env[++i])
		printf("%s\n", g_terminal.env[i]);
	return (STATUS_SUCCESS);
}

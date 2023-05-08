/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:01:23 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/08 18:58:13 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen_2d(char **a)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
		i++;
	return (i);
}

int	pos_equal(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (i);
	}
	return (0);
}

char	**env_variable_replaced(char **env, char *name)
{
	char	**new_env;
	int		length;
	int		flag;

	length = -1;
	flag = 0;
	new_env = clone_env(env);
	while (new_env[++length])
	{
		if (ft_strncmp(new_env[length], name, pos_equal(new_env[length])) == 0)
		{
			ft_replace(new_env[length], new_env[length], name);
			flag = 1;
		}
	}
	if (flag == 0)
	{
		free(new_env);
		new_env = increase_env(env);
		new_env[length + 1] = name;
	}
	free(env);
	return (new_env);
}

int	execute_export(t_cmd *cmd)
{
	char	**env;

	env = NULL;
	env = env_variable_replaced(g_terminal.env, cmd->args[1]);
	if (env)
		return (STATUS_SUCCESS);
	return (STATUS_ERROR);
}

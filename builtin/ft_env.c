/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:43:37 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/02 14:57:19 by lliberal         ###   ########.fr       */
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
	while (a && a[i])
		i++;
	return (i);
}

char	**synchronize_env_adding(char **env, char *cmd)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = increase_env(env);
	while (new_env[++i])
		new_env[i] = new_env[i];
	new_env[i] = ft_strdup(cmd);
	free_2d(env);
	return (new_env);
}

char	**synchronize_env(char *cmd)
{
	char	*tmp;
	char	**new;
	int		i;
	size_t	length;
	int		len;

	i = -1;
	len = 0;
	length = ft_strlen(cmd, '=');
	new = clone_env(g_terminal.env);
	free_2d(g_terminal.env);
	while (new[++i])
	{
		len = ft_strlen(new[i], '=');
		if (ft_strncmp(new[i], cmd, len) == 0 && new[i][len == '='])
		{
			tmp = new[i];
			new[i] = ft_replace(new[i], new[i], cmd);
			free(tmp);
		}
	}
	return (new);
}

int	execute_env(t_cmd *cmd)
{
	int	i;
	int	fd[2];

	i = -1;
	pipe(fd);
	(void) cmd;
	if (!cmd->next)
	{
		while (g_terminal.env[++i])
			printf("%s\n", g_terminal.env[i]);
	}
	else
	{
		while (g_terminal.env[++i])
		{
			write(fd[1], g_terminal.env[i], ft_strlen(g_terminal.env[i], 0));
			write(fd[1], "\n", 1);
		}
		close(fd[1]);
		cmd->next->fd_master[0] = fd[0];
	}
	return (STATUS_SUCCESS);
}

char	*find_var(char *var)
{
	t_expo		*tmp;
	size_t		len_var;

	tmp = g_terminal.expo;
	len_var = 0;
	while (tmp)
	{

		len_var = ft_strlen(tmp->variable, '=');
		if (ft_strlen(var, 0) == len_var && ft_strncmp(tmp->variable, var, len_var) == 0)
		{
			// printf("OK: %s\n", tmp->value);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return ("");
}

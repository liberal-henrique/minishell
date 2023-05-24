/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:43:37 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/24 18:41:41 by lliberal         ###   ########.fr       */
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
	free(env);
	return (new_env);
}

char	**synchronize_env(char *cmd)
{
	char	**new;
	int		i;
	size_t	length;
	int		len_variable;

	i = -1;
	len_variable = 0;
	length = ft_strlen(cmd, '=');
	new = clone_env(g_terminal.env);
	while (new[++i])
	{
		if (ft_strlen(new[i], '=') > length)
			len_variable = ft_strlen(new[i], '=');
		else
			len_variable = length;
		if (ft_strncmp(new[i], cmd, len_variable) == 0)
			new[i] = ft_replace(new[i], new[i], cmd);
	}
	free_2d(g_terminal.env);
	return (new);
}

int	execute_env(t_cmd *cmd)
{
	int	i;
	int	fd[2];

	i = -1;
	pipe(fd);
	(void) cmd;
	if(!cmd->next)
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
	int			len_var;
	char		*exp;

	tmp = g_terminal.expo;
	len_var = 0;
	exp = NULL;
	while (tmp)
	{
		len_var = ft_strlen(tmp->variable, '=');
		if (ft_strncmp(tmp->variable, var, len_var) == 0 && tmp->variable[len_var] == '=')
		{
			exp = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (exp);
}

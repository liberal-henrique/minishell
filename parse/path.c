/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/04 14:51:35 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path_join(char *s1, char *s2)
{
	int		i;
	int		k;
	int		len1;
	int		len2;
	char	*new;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)malloc(len1 + len2 + 2);
	if (!new)
		return (NULL);
	i = -1;
	k = -1;
	while (++i < len1)
		new[i] = s1[i];
	new[i++] = '/';
	while (++k < len2)
		new[i++] = s2[k];
	new[i] = 0;
	return (new);
}

char	*get_path(char **env)
{
	int	i;
	// int	length;

	i = -1;
	// length = ft_strlen(env[i]) - 1;
	while (env[++i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' \
		&& env[i][2] == 'T' && env[i][3] == 'H')
			return (env[i]);
	}
	return (NULL);
}
// return (ft_substring(env[i], 5, length));

char	*get_gpath(char **env, char **args)
{
	char	**path;
	char	*new_path;
	char	*cmd;
	int		i;

	i = -1;
	cmd = args[0];
	g_terminal.path = get_path(env);
	path = ft_split(g_terminal.path, ':');
	while (path && path[++i])
	{
		new_path = path_join(path[i], cmd);
		if (access(new_path, F_OK) == 0)
		{
			free_2d(path);
			return (new_path);
		}
		free(new_path);
	}
	free_2d(path);
	return (ft_strdup(args[0]));
}

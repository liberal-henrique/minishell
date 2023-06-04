/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 17:01:22 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

char	*path_join(char *s1, char *s2)
{
	int		i;
	int		k;
	int		len1;
	int		len2;
	char	*new;

	len1 = ft_strlen(s1, 0);
	len2 = ft_strlen(s2, 0);
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

char	*get_path(char **env, char *str)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' \
		&& env[i][2] == 'T' && env[i][3] == 'H')
			return (ft_substring(env[i], 5, ft_strlen(env[i], 0)));
	}
	return (ft_strdup(str));
}

char	*get_gpath(char **env, char **args)
{
	char	*single_path;
	char	**path;
	char	*new_path;
	char	*cmd;
	int		i;

	i = -1;
	cmd = args[0];
	single_path = get_path(env, cmd);
	path = ft_split(single_path, ':');
	free(single_path);
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

int	check_interrogation(char *str)
{
	int	len;

	if (ft_strlen(str, 0) > 2)
		len = ft_strlen(str, 0);
	else
		len = ft_strlen("$?", 0);
	return (len);
}

int	execute_directory(t_cmd *cmd, int fd)
{
	DIR	*dir;

	dir = opendir(cmd->args[0]);
	fd = open(cmd->args[0], O_RDONLY, 0777);
	if (dir != NULL)
	{
		closedir(dir);
		g_terminal.status = 126 + (write(2, "bash: ", 6) == 0);
		write(2, cmd->args[0], ft_strlen(cmd->args[0], 0));
		return (write(2, ": Is a directory\n", 17));
	}
	else if (fd != -1)
	{
		close(fd);
		g_terminal.status = 126 + (write(2, "bash: ", 6) == 0);
		write(2, cmd->args[0], ft_strlen(cmd->args[0], 0));
		return (write(2, ": Permission denied\n", 20));
	}
	else if (cmd->gpath && *cmd->gpath == '/')
	{
		g_terminal.status = 127 + (write(2, "bash: ", 6) == 0);
		write(2, cmd->args[0], ft_strlen(cmd->args[0], 0));
		return (write(2, ": No such file or directory\n", 28));
	}
	return (0);
}

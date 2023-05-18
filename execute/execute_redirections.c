/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:05:01 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/18 10:06:16 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

int	execute_redirection_out(t_cmd *cmd)
{
	char		buf[1025];
	int			n_bytes;
	int			length;
	int			fd;

	if (!cmd->args[1])
	{
		length = ft_strlen("zsh: parse error near `\n'", 0);
		write(2, "zsh: parse error near `\n'", length);
		return (1);
	}
	fd = open(cmd->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	n_bytes = 1;
	while (n_bytes > 0)
	{
		printf("%i\n", cmd->fd[0]);
		n_bytes = read(cmd->fd[0], buf, 1024);
		if (n_bytes > 0)
		{
			buf[n_bytes] = 0;
			write(fd, buf, n_bytes);
		}
	}
	close(fd);
	deallocate(g_terminal.begin);
	return (STATUS_SUCCESS);
}

int	execute_redirection_append_out(t_cmd *cmd)
{
	char		buf[1025];
	int			n_bytes;
	int			length;
	int			fd;

	if (!cmd->args[1])
	{
		length = ft_strlen("zsh: parse error near `\n'", 0);
		write(2, "zsh: parse error near `\n'", length);
		return (1);
	}
	fd = open(cmd->args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	n_bytes = 1;
	while (n_bytes > 0)
	{
		n_bytes = read(cmd->fd[0], buf, 1024);
		if (n_bytes > 0)
		{
			buf[n_bytes] = 0;
			write(fd, buf, n_bytes);
		}
	}
	close(fd);
	deallocate(g_terminal.begin);
	return (STATUS_SUCCESS);
}



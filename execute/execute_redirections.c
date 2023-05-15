/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:05:01 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/10 15:17:36 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

int	execute_redirection_out(t_cmd *cmd, int in)
{
	char		buf[1025];
	int			n_bytes;
	int			length;
	//int			fd;

	if (!cmd->args[1])
	{
		length = ft_strlen("zsh: parse error near `\n'", 0);
		write(2, "zsh: parse error near `\n'", length);
		return (1);
	}
	cmd->fd[1] = open(cmd->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd[1] == -1)
		return (-1);
	n_bytes = 1;
	while (n_bytes > 0)
	{
		n_bytes = read(in, buf, 1024);
		if (n_bytes > 0)
		{
			buf[n_bytes] = 0;
			write(cmd->fd[1], buf, n_bytes);
		}
	}
	close(cmd->fd[1]);
	close(cmd->fd[0]);
	deallocate(g_terminal.begin);
	return (STATUS_SUCCESS);
}

int	execute_redirection_in(t_cmd *cmd, int in)
{
	char	buf[1025];
	int		n_bytes;
	int		length;

	if (!cmd->args[1])
	{
		length = ft_strlen("zsh: parse error near `\n'", 0);
		write(2, "zsh: parse error near `\n'", length);
		return (1);
	}
	in = open(cmd->args[1], O_RDONLY, 0444);
	if (in == -1)
		return (-1);
	n_bytes = 1;
	while (n_bytes > 0)
	{
		n_bytes = read(in, buf, 1024);
		if (n_bytes > 0)
		{
			buf[n_bytes] = 0;
			write(cmd->fd[1], buf, n_bytes);
		}
	}
	close(cmd->fd[1]);
	close(cmd->fd[0]);
	deallocate(g_terminal.begin);
	return (STATUS_SUCCESS);
}

int	execute_redirection_heredoc(t_cmd *cmd, int in)
{
	int		length;
	char	*del;
	char	*line;
	char	*total;
	(void)in;

	if (!cmd->args[1])
	{
		length = ft_strlen("zsh: parse error near `\n'", 0);
		write(2, "zsh: parse error near `\n'", length);
		return (1);
	}
	del = cmd->args[1];
	total = malloc(1);
	total[0] = 0;
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, del, ft_strlen(del, 0)))
		{
			free(line);
			break ;
		}
		line = ft_strjoin(line, "\n");
		total = ft_strjoin(total, line);
		free(line);
	}
	//printf("total: %s\n", total);
	write(cmd->fd[1], total, ft_strlen(total, 0));
	close(cmd->fd[1]);
	close(cmd->fd[0]);
	deallocate(g_terminal.begin);
	return (STATUS_SUCCESS);
}

int	execute_redirection_append_out(t_cmd *cmd, int in)
{
	char		buf[1025];
	int			n_bytes;
	int			length;
	//int			fd;

	if (!cmd->args[1])
	{
		length = ft_strlen("zsh: parse error near `\n'", 0);
		write(2, "zsh: parse error near `\n'", length);
		return (1);
	}
	cmd->fd[1] = open(cmd->args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd[1] == -1)
		return (-1);
	n_bytes = 1;
	while (n_bytes > 0)
	{
		n_bytes = read(in, buf, 1024);
		if (n_bytes > 0)
		{
			buf[n_bytes] = 0;
			write(cmd->fd[1], buf, n_bytes);
		}
	}
	close(cmd->fd[1]);
	close(cmd->fd[0]);
	deallocate(g_terminal.begin);
	return (STATUS_SUCCESS);
}

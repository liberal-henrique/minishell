/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:05:01 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/24 15:57:20 by lliberal         ###   ########.fr       */
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

int	ft_heredoc(t_cmd *cmd, char *delimiter)
{
	char	*line;
	int		len;
	char	*buf;
	int		fd[2];

	pipe(fd);
	len = ft_strlen(delimiter, 0);
	buf = NULL;
	line = NULL;
	while (1)
	{
		line = readline(">");
		line = expander(g_terminal.env, line);
		if (!ft_strncmp(line, delimiter, len))
			break ;
		buf = ft_strjoin_rodraska(buf, line);
		free(line);
	}
	write(fd[1], buf, ft_strlen(buf, 0));
	close(fd[1]);
	cmd->fd_master[0] = fd[0];
	return (STATUS_SUCCESS);
}

char	*ft_strjoin_rodraska(char *line, char *buf)
{
	char	*new_line;
	int		i;
	int		k;
	int		buf_len;
	int		line_len;

	buf_len = ft_strlen(buf, 0);
	line_len = ft_strlen(line, 0);
	new_line = (char *)malloc(buf_len + line_len + 2);
	if (!new_line)
		return (NULL);
	i = -1;
	k = -1;
	while (++i < line_len)
		new_line[i] = line[i];
	while (++k < buf_len)
		new_line[i++] = buf[k];
	new_line[i++] = '\n';
	new_line[i] = 0;
	free(line);
	return (new_line);
}

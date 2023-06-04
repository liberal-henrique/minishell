/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:05:01 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 13:29:13 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

int	execute_redirection_out(t_cmd *cmd)
{
	char		buf[1025];
	int			n_bytes;
	int			fd;

	if (!cmd->args[1])
		return (write(2, "zsh: parse error near `\n'", \
		ft_strlen("zsh: parse error near `\n'", 0)) > 0);
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
	deallocate(g_terminal.list);
	return (STATUS_SUCCESS);
}

int	last_quote(char *s, char **set)
{
	if ((s[ft_strlen(s, '\'')] == '\'') || (s[ft_strlen(s, '\"')] == '\"'))
	{
		**set = 1;
		return (1);
	}
	return (0);
}

char	*check_delimiter(char *delimiter, char *set, int start, int i)
{
	char	*new;
	int		end;

	new = NULL;
	end = 0;
	*set = 0;
	if (!delimiter || last_quote(delimiter, &set))
		return (ft_strdup(delimiter));
	while (delimiter[++i])
	{
		if (*set == 0 && (delimiter[i] == '\'' || delimiter[i] == '\"'))
		{
			start = i + 1;
			*set = 1;
		}
		else if (*set == 1 && (delimiter[i] == '\'' || delimiter[i] == '\"'))
			end = i;
	}
	if (start == 0)
		end = ft_strlen(delimiter, 0);
	new = ft_substring(delimiter, start, end);
	return (new);
}

void	ft_heredoc2(char *delimiter, char *buf, int *fd, char sep)
{
	char	*line;

	while (!g_terminal.stopheredoc)
	{
		line = readline(">");
		if (!line && ft_strlen(line, 0) == 0 && !g_terminal.stopheredoc)
		{
			write(2, "bash: warning: here-document at line 1 \
			delimited by end-of-file (wanted `", 73);
			write(2, delimiter, ft_strlen(delimiter, 0));
			write(2, "')\n", 3);
			break ;
		}
		if (sep == 0)
			line = expander(line, 0);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter, 0)))
		{
			free(line);
			break ;
		}
		buf = ft_strjoin_rodraska(buf, line);
		free(line);
	}
	write(fd[1], buf, ft_strlen(buf, 0));
	free(buf);
	close(fd[1]);
}

int	ft_heredoc(t_cmd *cmd, char *delimiter, char *buf, int len)
{
	int		fd[2];
	char	sep;

	g_terminal.heredoc = 1;
	g_terminal.in_cmd = 0;
	pipe(fd);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		delimiter = check_delimiter(delimiter, &sep, 0, -1);
		if (sep == 0)
			delimiter = expander(delimiter, 0);
		len = ft_strlen(delimiter, 0);
		ft_heredoc2(delimiter, buf, fd, sep);
		free(delimiter);
		exit (0);
	}
	g_terminal.heredoc = 0;
	waitpid(cmd->pid, 0, 0);
	cmd->pid = -1;
	close(fd[1]);
	cmd->fd_master[0] = fd[0];
	return (g_terminal.status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:05:01 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/02 00:05:35 by lliberal         ###   ########.fr       */
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

char	*check_delimiter(char *delimiter, char *set, int start, int i)
{
	char	*new;
	int		end;

	new = NULL;
	end = 0;
	*set = 0;
	if (!delimiter)
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

/* void	sighear(int	sig)
{
	if (sig == SIGINT)
	{
		// limpar tudo e dar exit do processo;
	}
} */



int	ft_heredoc(t_cmd *cmd, char *delimiter, char *buf, int len)
{
	char	*line;
	char	set;
	int		fd[2];
	int		pid;
	int		wstatus;

	g_terminal.heredoc = 1;
	g_terminal.in_cmd = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		delimiter = check_delimiter(delimiter, &set, 0, -1);
		if (set == 0)
			delimiter = expander(delimiter);
		len = ft_strlen(delimiter, 0);
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
			if (set == 0)
				line = expander(line);
			if (!ft_strncmp(line, delimiter, len))
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
		free(delimiter);
		exit (130);
	}
	g_terminal.heredoc = 0;
	close(fd[1]);
	cmd->fd_master[0] = fd[0];
	//waitpid(pid, NULL, 0);
	waitpid(pid, &wstatus, WUNTRACED);
	wstatus = WEXITSTATUS(wstatus);
	g_terminal.status = wstatus;
	//printf("terminal status: %d\n", g_terminal.status);
	//g_terminal.status = 130;
	return (g_terminal.status);
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

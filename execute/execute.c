/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/02 00:15:25 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

void	close_shit(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->fd[0] > 2)
			close(temp->fd[0]);
		if (temp->fd[1] > 2)
			close(temp->fd[1]);
		if (temp->fd_master[0] > 2)
			close(temp->fd_master[0]);
		if (temp->fd_master[1] > 2)
			close(temp->fd_master[1]);
		temp = temp->next;
	}
	cmd = temp;
}

/* int	execute_main(t_cmd *cmd, int in, int out)
{
	if (ft_compare(cmd->args[0], "cd"))
	{
		execute_cd(cmd);
		if (cmd->next)
			execute_main(cmd->next, cmd->fd[0], cmd->fd[1]);
		return (0);
	}
	if (ft_compare(cmd->args[0], "export"))
	{
		execute_export(cmd);
		if (cmd->next)
			execute_main(cmd->next, cmd->fd[0], cmd->fd[1]);
		return (0);
	}
	if (ft_compare(cmd->args[0], "unset"))
	{
		execute_unset(cmd);
		if (cmd->next)
			execute_main(cmd->next, cmd->fd[0], cmd->fd[1]);
		return (0);
	}
	if (ft_compare(cmd->args[0], "env"))
	{
		execute_env(cmd);
		if (cmd->next)
			execute_main(cmd->next, cmd->fd[0], cmd->fd[1]);
		return (0);
	}
	if (out > 0)
		close(out);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd->fd_master[0] > 2)
			dup2(cmd->fd_master[0], STDIN_FILENO);
		if (cmd->fd_master[0] < 3)
			dup2(in, STDIN_FILENO);
		if (cmd->fd_master[1] > 2)
			dup2(cmd->fd_master[1], STDOUT_FILENO);
		if (cmd->fd_master[1] < 3)
			dup2(cmd->fd[1], STDOUT_FILENO);
		close_shit(cmd);
		exit(cmd->execute(cmd, in));
	}
	if (in != STDIN_FILENO)
		close(in);
	if (cmd->next)
		execute_main(cmd->next, cmd->fd[0], cmd->fd[1]);
	return (STATUS_SUCCESS);
} */

int	cnt_here(t_cmd *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt_here(node->next));
}

int	execute_directory(t_cmd *cmd)
{
	DIR	*dir;
	int	fd;

	dir = opendir(cmd->args[0]);
	fd = open(cmd->args[0], O_RDONLY, 0777);
	if (dir != NULL)
	{
		g_terminal.status = 126;
		write(2, "bash: ", 6);
		write(2, cmd->args[0], ft_strlen(cmd->args[0], 0));
		write(2, ": Is a directory\n", 17);
	}
	else if (fd != -1)
	{
		g_terminal.status = 126;
		write(2, "bash: ", 6);
		write(2, cmd->args[0], ft_strlen(cmd->args[0], 0));
		write(2, ": Permission denied\n", 20);
	}
	else
	{
		g_terminal.status = 127;
		write(2, "bash: ", 6);
		write(2, cmd->args[0], ft_strlen(cmd->args[0], 0));
		write(2, ": No such file or directory\n", 28);
	}
	closedir(dir);
	close(fd);
	return (g_terminal.status);
}

int	execute_main(t_cmd *cmd, int in, int out)
{
	int	len_cmd;

	len_cmd = cnt_here(cmd);
	while (cmd)
	{
		if (ft_compare(cmd->args[0], "cd"))
			execute_cd(cmd);
		else if (ft_compare(cmd->args[0], "export"))
			execute_export(cmd);
		else if (ft_compare(cmd->args[0], "unset"))
			execute_unset(cmd);
		else if (ft_compare(cmd->args[0], "env"))
			execute_env(cmd);
		else if (!ft_strncmp(cmd->args[0], "./", 2) || !ft_strncmp(cmd->args[0], "/", 1))
			execute_directory(cmd);
		else if (ft_compare(cmd->args[0], "exit"))
			execute_exit(cmd, len_cmd);
		else
			execute_geral(cmd, in, out);
		if (cmd->next)
		{
			in = cmd->fd[0];
			out = cmd->fd[1];
		}
		cmd = cmd->next;
	}
	return (0);
	/* g_terminal.status = STATUS_SUCCESS;
	return (g_terminal.status); */
}

int	execute_geral(t_cmd *cmd, int in, int out)
{
	if (out > 0)
		close(out);
	(void)out;
	cmd->pid = fork();
	g_terminal.childs = 1;
	if (cmd->pid == 0)
	{
		if (cmd->fd_master[0] > 2)
			dup2(cmd->fd_master[0], STDIN_FILENO);
		if (cmd->fd_master[0] < 3)
			dup2(in, STDIN_FILENO);
		if (cmd->fd_master[1] > 2)
			dup2(cmd->fd_master[1], STDOUT_FILENO);
		if (cmd->fd_master[1] < 3)
			dup2(cmd->fd[1], STDOUT_FILENO);
		close_shit(cmd);
		exit(cmd->execute(cmd, in));
	}
	if (in != STDIN_FILENO)
		close(in);
	g_terminal.status = STATUS_SUCCESS;
	return (g_terminal.status);
}



int	execute_default(t_cmd *cmd)
{
	// char	**clone;

	// clone = clone_env(g_terminal.env);
	// ft_strcpy(clone[find_env(clone)], ft_strjoin("SHLVL=", ft_itoa((ft_atoi(find_var("SHLVL="), 0, 0, 1)+ 1))));
	// write(2, ft_itoa((ft_atoi(find_var("SHLVL="), 0, 0, 1)+ 1)), sizeof(ft_itoa((ft_atoi(find_var("SHLVL="), 0, 0, 1)+ 1))));
	// if (execve(cmd->gpath, cmd->args, clone) == -1)
	if (execve(cmd->gpath, cmd->args, g_terminal.env) == -1)
	{
		write(2, "command not found: ", 19);
		write(2, cmd->args[0], ft_strlen(cmd->args[0], 0));
		write(2, "\n", 1);
		g_terminal.status = 127;
		return (g_terminal.status);
	}
	return (220);
}

int	find_env(char **env)
{
	int	f;

	f = -1;
	while (ft_strncmp(env[++f], "SHLVL=", 6));
	return (f);
}

void	ft_wait(t_cmd *cmd)
{
	t_cmd	*temp;
	int		wstatus;

	temp = cmd;
	while (cmd)
	{
		waitpid(-1, &wstatus, WUNTRACED);
		wstatus = WEXITSTATUS(wstatus);
		g_terminal.status = wstatus;
		cmd = cmd->next;
	}
	while (temp)
	{
		if (temp->fd[0] > 2)
			close(temp->fd[0]);
		if (temp->fd[1] > 2)
			close(temp->fd[1]);
		if (temp->fd_master[0] > 2)
			close(temp->fd_master[0]);
		if (temp->fd_master[1] > 2)
			close(temp->fd_master[1]);
		temp = temp->next;
	}

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/25 16:21:58 by lliberal         ###   ########.fr       */
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

int	execute_main(t_cmd *cmd, int in, int out)
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
}

int	execute_default(t_cmd *cmd)
{
	//printf("fd_master[0] :%d\n", cmd->fd_master[0]);
	// if (!cmd->gpath)
	// 	return (0);
	if (execve(cmd->gpath, cmd->args, g_terminal.env) == -1)
	{
		printf("%s%s\n", cmd->args[0], ": command not found");
		g_terminal.status = 127;
		return (g_terminal.status);
	}
	return (220);
}

void	ft_wait(t_cmd *cmd)
{
	int	wstatus;
	t_cmd *temp = cmd;

	while (cmd)
	{
		waitpid(-1, &wstatus, WUNTRACED);
		// close (STDOUT_FILENO);
		wstatus = WEXITSTATUS(wstatus);
		g_terminal.status = wstatus;
		// dprintf(2, "t: %i\n", wstatus);
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

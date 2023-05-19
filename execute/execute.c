/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/19 13:54:12 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

int	execute_main(t_cmd *cmd, int in)
{
	// O CD tera de aceitar um proximo argumento para tratar do absolute path
	if (!cmd->next && (ft_compare(cmd->args[0], "cd")))
		return execute_cd(cmd);
	if (!cmd->next && (ft_compare(cmd->args[0], "export")))
		return execute_export(cmd);
	if (!cmd->next && (ft_compare(cmd->args[0], "unset")))
		return execute_unset(cmd);
	if (!cmd->next && (ft_compare(cmd->args[0], "env")))
		return execute_env(cmd);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd->fd_master[0] > 2)
			dup2(cmd->fd_master[0], STDIN_FILENO);
		if (cmd->fd_master[0] < 3)
			dup2(in, STDIN_FILENO);
		if (cmd->fd_master[1] > 2)
			dup2(cmd->fd_master[1],STDOUT_FILENO);
		if (cmd->fd_master[1] < 3)
			dup2(cmd->fd[1], STDOUT_FILENO);
		exit(cmd->execute(cmd, in));
	}
	if (in != STDIN_FILENO)
		close(in);
	if (cmd->fd[1] != STDOUT_FILENO)
		close(cmd->fd[1]);
	if (cmd->next)
		execute_main(cmd->next, cmd->fd[0]);
	return (STATUS_SUCCESS);
}

int	execute_default(t_cmd *cmd)
{
	execve(cmd->gpath, cmd->args, g_terminal.env);
	return (127);
}

void	ft_wait(t_cmd *cmd)
{
	int	wstatus;

	while (cmd)
	{
		waitpid(-1, &wstatus, 0);
		wstatus = WEXITSTATUS(wstatus);
		g_terminal.status = wstatus;
		// dprintf(2, "t: %i\n", wstatus);
		cmd = cmd->next;
	}
}

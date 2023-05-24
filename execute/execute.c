/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/24 18:44:44 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

int	execute_main(t_cmd *cmd, int in, int out)
{
	if (/* !cmd->next && */ (ft_compare(cmd->args[0], "cd")))
	{
		execute_cd(cmd);
		if (cmd->next)
			execute_main(cmd->next, cmd->fd[0], cmd->fd[1]);
		return (0);
	}
	if (/* !cmd->next && */ (ft_compare(cmd->args[0], "export")))
	{
		execute_export(cmd);
		if (cmd->next)
			execute_main(cmd->next, cmd->fd[0], cmd->fd[1]);
		return (0);
	}
	if (/* !cmd->next && */ (ft_compare(cmd->args[0], "unset")))
	{
		execute_unset(cmd);
		if (cmd->next)
			execute_main(cmd->next, cmd->fd[0], cmd->fd[1]);
		return (0);
	}
	if (/* !cmd->next && */ (ft_compare(cmd->args[0], "env")))
	{
		execute_env(cmd);
		if (cmd->next)
			execute_main(cmd->next, cmd->fd[0], cmd->fd[1]);
		return (0);
	}
	if (out > 0)
	{
		//fprintf(stderr, "%d\n", out);
		close(out);
	}
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd->fd_master[0] > 2)
			dup2(cmd->fd_master[0], STDIN_FILENO) /* && close(cmd->fd_master[0]) */;
		if (cmd->fd_master[0] < 3)
			dup2(in, STDIN_FILENO) /* && in > 2 && close(in) */;
		if (cmd->fd_master[1] > 2)
			dup2(cmd->fd_master[1], STDOUT_FILENO) /* && close(cmd->fd_master[1]) */;
		if (cmd->fd_master[1] < 3)
			dup2(cmd->fd[1], STDOUT_FILENO) /* && cmd->fd[1] > 2 && !close(cmd->fd[1]) && fprintf(stderr, "fd: %d, %s\n", cmd->fd[1], cmd->args[0]) */;
		//g_terminal.status = cmd->execute(cmd, in);
		//exit(g_terminal.status);
		exit(cmd->execute(cmd, in));
	}
	//printf("%s fd[0]: %d\n", cmd->args[0], cmd->fd[0]);
	//printf("%s fd[1]: %d\n", cmd->args[0], cmd->fd[1]);
	if (in != STDIN_FILENO)
		close(in);
	// if (cmd->fd[0] > 2)
	// 	close(cmd->fd[0]);
/* 	if (out != STDOUT_FILENO)
		close(cmd->fd[1]); */
	/* if (cmd->fd[0] > 2)
		close(cmd->fd[0]);
	if (cmd->fd[1] > 2)
		close(cmd->fd[1]); */
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
		/* if (temp->fd[0] > 2)
			close(temp->fd[0]);
		if (temp->fd[1] > 2)
			close(temp->fd[1]);
		if (temp->fd_master[0] > 2)
			close(temp->fd_master[0]);
		if (temp->fd_master[1] > 2)
			close(temp->fd_master[1]); */
		temp = temp->next;
	}

}

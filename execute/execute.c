/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 16:56:20 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>

void	execute_main_2(t_cmd *cmd, int in, int out, int len_cmd)
{
	if (ft_compare(cmd->args[0], "cd"))
		execute_cd(cmd);
	else if (ft_compare(cmd->args[0], "export"))
		execute_export(cmd);
	else if (ft_compare(cmd->args[0], "unset"))
		execute_unset(cmd);
	else if (ft_compare(cmd->args[0], "env"))
		execute_env(cmd);
	else if (ft_compare(cmd->args[0], "exit"))
		execute_exit(cmd, len_cmd);
	else
		execute_geral(cmd, in, out);
}

int	execute_main(t_cmd *cmd, int in, int out)
{
	int	len_cmd;

	len_cmd = cnt_here(cmd);
	while (cmd)
	{
		if (cmd->stop == 1)
			cmd = cmd->next;
		else
		{
			execute_main_2(cmd, in, out, len_cmd);
			if (cmd->next)
			{
				in = cmd->fd[0];
				out = cmd->fd[1];
			}
			cmd = cmd->next;
		}
	}
	return (0);
}

void	execute_geral_2(t_cmd *cmd, int in)
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
}

int	execute_geral(t_cmd *cmd, int in, int out)
{
	int	pid;

	if (out > 0)
		close(out);
	(void)out;
	pid = fork();
	if (cmd->pid == -1)
		cmd->pid = pid;
	g_terminal.childs = 1;
	if (pid == 0)
	{
		execute_geral_2(cmd, in);
		exit(cmd->execute(cmd, in));
	}
	if (in != STDIN_FILENO)
		close(in);
	g_terminal.status = STATUS_SUCCESS;
	return (g_terminal.status);
}

int	execute_default(t_cmd *cmd)
{
	if (execve(cmd->gpath, cmd->args, g_terminal.env) == -1)
	{
		if (execute_directory(cmd, 0))
			exit (g_terminal.status);
		write(2, "command not found: ", 19);
		write(2, cmd->args[0], ft_strlen(cmd->args[0], 0));
		write(2, "\n", 1);
		g_terminal.status = 127;
		exit (g_terminal.status);
	}
	return (220);
}

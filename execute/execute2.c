/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 22:07:42 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 22:23:24 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

void	ft_wait(t_cmd *cmd)
{
	t_cmd	*temp;
	int		wstatus;

	temp = cmd;
	while (cmd)
	{
		if (cmd->pid != -1 && waitpid(cmd->pid, &wstatus, WUNTRACED) > 0)
		{
			wstatus = WEXITSTATUS(wstatus);
			g_terminal.status = wstatus;
		}
		else
			g_terminal.status = cmd->status;
		cmd = cmd->next;
	}
	close_shit(cmd);
}

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

int	cnt_here(t_cmd *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt_here(node->next));
}

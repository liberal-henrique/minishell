/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:34:24 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 13:42:17 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

int	redirect_1(t_token *tmp, t_cmd *cmd, int fd)
{
	write(2, "bash: ", 6);
	write(2, tmp->next->str, ft_strlen(tmp->next->str, 0));
	write(2, ": No such file or directory\n", 28);
	cmd->status = 1;
	cmd->stop = 1;
	close(fd);
	return (1);
}

int	redirect_2(t_token *tmp, t_cmd *cmd, int fd)
{
	write(2, "bash: ", 6);
	write(2, tmp->next->str, ft_strlen(tmp->next->str, 0));
	write(2, ": No such file or directory\n", 28);
	cmd->status = 1;
	cmd->stop = 1;
	close(fd);
	return (1);
}

int	redirect_4(t_token *tmp, t_cmd *cmd, int fd)
{
	write(2, "bash: ", 6);
	write(2, tmp->next->str, ft_strlen(tmp->next->str, 0));
	write(2, ": No such file or directory\n", 28);
	cmd->status = 1;
	cmd->stop = 1;
	close(fd);
	return (1);
}

int	redirect_pai(t_token *tmp, t_cmd *cmd, int fd, int f)
{
	if (f == 1)
		redirect_1(tmp, cmd, fd);
	else if (f == 2)
		redirect_2(tmp, cmd, fd);
	else if (f == 4)
		redirect_4(tmp, cmd, fd);
	return (1);
}

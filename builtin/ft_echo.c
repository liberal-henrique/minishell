/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:42 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/10 15:17:10 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_echo(t_cmd *cmd)
{
	int	i;

	i = ft_compare(cmd->args[1], "-n") + 1;
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i], 0));
		if (cmd->args[++i])
			write(1, " ", 1);
	}
	if (!ft_compare(cmd->args[1], "-n"))
		write(1, "\n", 1);
	// deallocate(g_terminal.begin);
	return (STATUS_SUCCESS);
}

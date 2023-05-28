/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:52:30 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/28 13:09:54 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_dollar(t_cmd *cmd)
{
	(void)cmd;
	dprintf(2, "command not found: %i\n", g_terminal.status);
	return (0);
}

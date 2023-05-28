/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:38:42 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/28 21:31:16 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_atoi(const char *str, int res, int i, int sign)
{
	if (!str)
		return (0);
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	execute_exit(t_cmd *cmd)
{
	int	n;
	int	status;

	n = -1;
	status = 0;
	while (cmd->args[++n])
		;
	if (n == 1)
		status = 0;
	else if (n == 2)
		status = ft_atoi(cmd->args[1], 0, 0, 1);
	else if (n == 3)
		status = STATUS_ERROR;
	printf("exit\n");
	rl_clear_history();
	exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:42 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/26 12:52:18 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_flag(char *str)
{
	//printf("str: %s\n", str);
	int	j;

	if (str[0] != '-')
		return (0);
	j = 0;
	while (str[++j])
	{
		if (str[j] != 'n')
			return (0);
	}
	return (1);
}

// int	execute_echo(t_cmd *cmd)
// {
// 	int	i;
// 	int	f;
// 	int flag;

// 	i = 0;
// 	f = 1;
// 	flag = 0;
// 	while (cmd->args[++i])
// 	{
// 		if (flag == 0)
// 			f = check_flag(cmd->args[i]);
// 		if (f == 0)
// 			flag = 1;
// 		//printf("f: %d\n", f);
// 		write(1, cmd->args[i], ft_strlen(cmd->args[i], 0));
// 		if (cmd->args[++i])
// 			write(1, " ", 1);
// 	}
// 	if (f == 1)
// 		write(1, "\n", 1);
// 	return (STATUS_SUCCESS);
// }



int	execute_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (check_flag(cmd->args[++i]))
			flag = 1;
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i], 0));
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (STATUS_SUCCESS);
}














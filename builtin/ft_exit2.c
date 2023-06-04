/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:38:42 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 17:26:16 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_all_num(char *str, int i);
long long	ft_atoi_long(const char *str, unsigned long \
res, int *error, long sign);
char		*ft_itoa_long(long long n);

int	exit_pipe(t_cmd *cmd, int status)
{
	cmd->pid = fork();
	g_terminal.childs = 1;
	if (cmd->pid == 0)
	{
		exit(status);
	}
	return (status);
}

int	check_args(int n, t_cmd *cmd)
{
	int	error;

	error = 0;
	while (cmd->args[++n])
		;
	if (n == 2)
	{
		g_terminal.status = ft_atoi_long(cmd->args[1], 0, &error, 1);
		if (error && write(2, ": numeric argument required\n", 28))
			g_terminal.status = 2;
	}
	else if (n >= 3 && write(2, "too many arguments\n", 19))
		return (status(cmd, 1));
	if (cmd->args[1] && !is_all_num(cmd->args[1], 0))
	{
		write(2, "bash: exit: ", 12);
		write(2, cmd->args[1], ft_strlen(cmd->args[1], 0));
		write(2, ": numeric argument required\n", 28);
		g_terminal.status = 2;
	}
	return (0);
}

int	execute_exit(t_cmd *cmd, int len_cmd)
{
	if (check_args(-1, cmd))
		return (g_terminal.status);
	write(2, "exit\n", 5);
	if (len_cmd < 2)
		rl_clear_history();
	else
		exit_pipe(cmd, g_terminal.status);
	close_shit(g_terminal.list);
	cleanall(g_terminal.list, 0);
	clean_expo(g_terminal.expo);
	free_2d(g_terminal.env);
	exit(g_terminal.status);
	return (g_terminal.status);
}

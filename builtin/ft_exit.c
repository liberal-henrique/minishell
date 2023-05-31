/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:38:42 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/31 23:07:11 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned int	nb_size_long(long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa_long(long long n)
{
	char		*str;
	int			len;
	long long	ln;

	ln = n;
	len = nb_size_long(ln);
	if (n < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	str = malloc_ob((len + 1));
	if (ln < 0)
	{
		str[0] = '-';
		ln *= -1;
	}
	len--;
	while (ln != 0)
	{
		str[len] = ln % 10 + 48;
		ln /= 10;
		len--;
	}
	return (str);
}

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

long long	ft_atoi_long(const char *str, long long res, int i, int sign)
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

int	exit_pipe(int status)
{
	int	pid;

	pid = fork();
	g_terminal.childs = 1;
	if (pid == 0)
	{
		exit(status);
	}
	return (status);
}

int	is_all_num(char *str, int i)
{
	if (!ft_isnum(str[0]) && str[0] != '+' && str[0] != '-')
		return (0);
	while (str[++i])
	{
		if (!ft_isnum(str[i]))
			return (0);
	}
	return (1);
}

// bash: exit: hello: numeric argument required
int	execute_exit(t_cmd *cmd, int len_cmd)
{
	long long status;
	int			n;
	char		*itoa;

	n = -1;
	status = 0;
	if (!is_all_num(cmd->args[1], 0))
	{
		write(2, "exit\n", 5);
		write(2, "bash: exit: ", 12);
		write(2, cmd->args[1], ft_strlen(cmd->args[1], 0));
		write(2, ": numeric argument required\n", 28);
		exit (2);
	}
	while (cmd->args[++n])
		;
	if (n == 1)
		status = 0;
	else if (n == 2)
		status = ft_atoi_long(cmd->args[1], 0, 0, 1);
	else if (n >= 3)
	{
		write(2, "exit: too many arguments\n", 25);
		exit(1);
	}
	itoa = ft_itoa_long(status);
	//printf("status: %lld\n", status);
	//printf("itoa: %s\n", itoa);
	//printf("arg: %s\n", cmd->args[1]);
	if (/* cmd->args[1][0] == '-' ||  */cmd->args[1][0] == '+')
	{
		if ((ft_strncmp(itoa, &cmd->args[1][1], ft_strlen(itoa, 0)) != 0))
		{
			free(itoa);
			exit(2);
		}
	}
	else if ((ft_strncmp(itoa, cmd->args[1], ft_strlen(itoa, 0)) != 0))
	{
		free(itoa);
		exit(2);
	}
	free(itoa);
	if (len_cmd < 2)
	{
		printf("exit\n");
		rl_clear_history();
		exit(status);
	}
	else
	{
		exit_pipe(status);
	}
	return (status);
}

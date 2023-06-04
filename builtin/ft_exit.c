/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:38:42 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 12:40:50 by lliberal         ###   ########.fr       */
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

long long	ft_atoi_long(const char *str, unsigned long \
res, int *error, long sign)
{
	int	i;

	i = 0;
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
	while (*error == 0 && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10LU) + (str[i] - '0');
		if ((sign == 1 && res > LONG_MAX) || res > 9223372036854775808LU)
			*error = (1 + (sign == 1));
		i++;
	}
	return (res * sign);
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

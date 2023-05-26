/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:00 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/21 18:23:10 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

size_t	ft_strlen(const char *a, char set)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
	{
		if (a[i] == set)
			break ;
		i++;
	}
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	return_len_value(char **env, char *str)
{
	size_t	length_received;
	int		len_var;
	int		len;
	int		i;

	i = -1;
	len = 0;
	len_var = 0;
	length_received = ft_strlen(str, 0);
	while (env[++i])
	{
		if (ft_strlen(env[i], '=') > length_received)
			len_var = ft_strlen(env[i], '=');
		else
			len_var = length_received;
		if (ft_strncmp(env[i], str, len_var) == 0)
			len = ft_strlen(env[i], 0) - (ft_strlen(env[i], '='));
	}
	return (len);
}

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	length_value(char **env, charchar *str)
{
	int		length;
	int		j;
	int		len;

	j = 0;
	length = 0;
	len = 0;
	while (*str)
	{
		if (j == 0 && *str++ == '\"')
			j = 1;
		else if (j == 1 && *str++ == '\"')
			j = 0;
		if (j == 1 && *str == '$')
		{
			*str++ = 5;
			while (!is_space(*str))
				[length++] = *str++;
			len += return_len_value(env, set);
		}
	}
	return (len);
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;

	char	set[] = "ola, $name. Como Esta o seu dia? Tu faras teu $PATH?";
	printf("%i\n", length_value(env, set));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:07:01 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 00:22:22 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// verify a char
int	contain_char(char *s, char c)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		if (*tmp == c)
			return (1);
		tmp++;
	}
	return (0);
}

int	ft_compare(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

int	check_contain(char *origin, char *set)
{
	int	position;
	int	i;
	int	j;

	i = -1;
	position = 0;
	while (set && origin[++i])
	{
		j = 0;
		while (origin[i] && set[j] && origin[i] == set[j])
		{
			if (j == 0)
				position = i;
			i++;
			j++;
		}
		if (set[j] == '\0')
			return (position);
	}
	return (-1);
}

char	*ft_replace(char *dst, char *to, char *rep)
{
	char	*new;
	int		start;
	int		i;
	int		j;

	start = check_contain(dst, to);
	if (start < 0 || !to || !rep)
		return (ft_strdup(dst));
	new = malloc_ob((ft_strlen(dst, 0) - \
	(ft_strlen(to, 0)) + ft_strlen(rep, 0) + 1));
	j = -1;
	i = 0;
	while (dst[++j])
	{
		if (j == start)
			while (*rep)
				new[i++] = *rep++;
		if (j == start)
			j += (ft_strlen(to, 0) - 1);
		else
			new[i++] = dst[j];
	}
	return (new);
}

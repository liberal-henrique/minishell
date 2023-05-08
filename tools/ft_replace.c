/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:07:01 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/08 17:48:43 by lliberal         ###   ########.fr       */
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

// verify a string
int	check_contain(char *origin, char *set)
{
	int	i;
	int	j;
	int	position;

	i = -1;
	position = 0;
	while (origin[++i])
	{
		j = 0;
		while (origin[i] == set[j] && origin[i])
		{
			if (j == 0)
				position = i;
			i++;
			j++;
		}
		if (!set[j])
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
	if (start < 0)
		return (NULL);
	new = malloc_ob(((ft_strlen(dst) - ft_strlen(to)) + ft_strlen(rep) + 1));
	if (!new)
		return (NULL);
	j = -1;
	i = 0;
	while (dst[++j])
	{
		if (i == start)
			j += (ft_strlen(to) - 1);
		if (i == start)
			while (*rep)
				new[i++] = *rep++;
		else
			new[i++] = dst[j];
	}
	return (new);
}

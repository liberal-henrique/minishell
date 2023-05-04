/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:58:39 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/04 14:02:41 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**split_rec(char **res, char *str, int cnt, char c)
{
	int		index;
	char	*keep_parts;

	index = 0;
	keep_parts = NULL;
	while (*str == c)
		str++;
	while (str[index] != c && str[index])
		index++;
	if (index > 0)
		keep_parts = malloc(sizeof(char) * (index + 1));
	index = 0;
	while (keep_parts && *str != c && *str)
		keep_parts[index++] = *str++;
	if (keep_parts)
		keep_parts[index] = '\0';
	if (keep_parts)
		res = split_rec(res, str, cnt + 1, c);
	else
		res = malloc_ob(sizeof(char *) * (cnt + 1));
	if (res)
		res[cnt] = keep_parts;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	return (split_rec(0, (char *)s, 0, c));
}

void	free_2d(char **result)
{
	int	i;

	i = 0;
	while (result && result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:58:39 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 10:14:02 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* static char	**split_rec(char **res, char *str, int cnt, char c)
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
} */
int	string_counter(char const *str, char c)
{
	int	i;
	int	ver;
	int	count;

	i = 0;
	ver = 1;
	count = 0;
	while (str[i])
	{
		while (str[i] != '\0' && str[i] == c)
		{
			i++;
			ver = 1;
		}
		if (str[i] != '\0' && str[i] != c && ver == 1)
		{
			i++;
			count++;
			ver = 0;
		}
		else if (str[i] != c && str[i] != 0)
			i++;
	}
	return (count);
}

char	*word(char const *str, int *ptr_i, char c)
{
	int		i;
	int		n;
	int		k;
	char	*word;

	i = *ptr_i;
	n = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
		n++;
	}
	word = malloc_ob((n + 1));
	if (!word)
		return (NULL);
	i = i - n;
	k = 0;
	while (str[i] != '\0' && str[i] != c)
		word[k++] = str[i++];
	*ptr_i = i;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		i;
	int		w;
	char	**arr;

	count = string_counter(s, c);
	arr = malloc_ob(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	w = 0;
	while (w < count && s[i])
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			arr[w] = word(s, &i, c);
			w++;
		}
		i++;
	}
	return (arr);
}

void	free_2d(char **result)
{
	int	i;

	i = 0;
	if (!result)
		return ;
	while (result && result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

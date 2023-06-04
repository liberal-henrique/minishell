/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 22:28:55 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 12:53:05 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| (c >= '0' && c <= '9') || (c == '_'));
}

char	*dollar(char *str, int *flag)
{
	*flag = 0;
	if ((!ft_strcmp(str, "$EMPTY") || !ft_strcmp(str, "$!") \
	|| !ft_strcmp(str, "$;")) && ++*flag)
	{
		free(str);
		str = ft_strdup("");
	}
	else if (!ft_strncmp(str, "$?", check_interrogation(str)) && ++*flag)
	{
		free(str);
		str = ft_itoa(g_terminal.status);
	}
	else if (str[0] == '$' && !str[1] && ++*flag)
	{
		free(str);
		str = ft_strdup("$");
	}
	else if (str[0] == '$' && str[1] && str[1] != '?' \
	&& check_group(str[1]) && ++*flag)
	{
		free(str);
		str = ft_strdup("");
	}
	return (str);
}

char	*remove_quotes(char *str)
{
	char	*new;
	char	*temp;
	char	s;
	int		i;

	s = 0;
	i = 0;
	temp = str;
	if (!str)
		return (str);
	new = malloc_ob(ft_strlen(str, 0) * 2);
	while (*str)
	{
		if (s == 0 && (*str == '\'' || *str == '\"'))
			s = *str;
		else if (*str == s)
			s = 0;
		else
			new[i++] = *str;
		str++;
	}
	free(temp);
	return (new);
}

char	*find_needle2(char *stack, char *needle, char set, int i)
{
	int		k;
	char	*new;
	char	*itoa;

	while (stack[++i])
	{
		k = 0;
		if (stack[i] == '\'' && set == 0)
			set = 1;
		else if (stack[i] == '\'' && set == 1)
			set = 0;
		while (stack[i + k] == needle[k] && needle[k] != '\0')
			k++;
		if (k == (int)ft_strlen(needle, 0) && set == 0)
		{
			new = ft_strdup(stack);
			free(stack);
			itoa = ft_itoa(g_terminal.status);
			stack = ft_replace(new, needle, itoa);
			free(itoa);
			free(new);
		}
	}
	return (stack);
}

char	*find_needle(char *stack, char *needle, char set)
{
	if (!stack || !needle)
		return (stack);
	return (find_needle2(stack, needle, set, -1));
}

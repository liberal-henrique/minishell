/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 22:28:55 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 22:44:34 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| (c >= '0' && c <= '9') || (c == '_'));
}

char	*dollar(char *str)
{
	if (!ft_strcmp(str, "$EMPTY") || !ft_strcmp(str, "$!"))
	{
		free(str);
		str = ft_strdup("");
		return (str);
	}
	if (!ft_strcmp(str, "$?"))
	{
		free(str);
		str = ft_itoa(g_terminal.status);
		return (str);
	}
	if (!ft_strcmp(str, "$;"))
	{
		free(str);
		str = ft_strdup("");
		return (str);
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

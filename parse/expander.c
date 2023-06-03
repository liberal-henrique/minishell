/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:31:20 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 00:21:21 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	expander3(char *str, char *sep, int index)
{
	if (*sep == 0 && (str[index] == '\'' || str[index] == '\"'))
			*sep = str[index];
	else if (str[index] == *sep)
		*sep = 0;
}

char	*expander2(char *str, char *name, int *start, char sep)
{
	int		index;
	int		end;

	end = 0;
	index = -1;
	while (str[++index] && end == 0)
	{
		expander3(str, &sep, index);
		if (sep != '\'' && *start == -1 && str[index] == '$')
		{
			if (!str[index + 1] || str[index + 1] == '.')
			{
				free(name);
				return (str);
			}
			*start = index;
		}
		else if (*start >= 0 && !check(str[index]) && ++end)
			name[index] = 0;
		if (end == 0 && *start != -1)
			name[index - *start] = str[index];
	}
	return (name);
}

char	*expander(char *str, char sep)
{
	char	*name;
	int		start;
	char	*new;

	start = -1;
	str = find_needle(str, "$?", 0);
	name = malloc_ob(1024);
	name = expander2(str, name, &start, sep);
	if (start == -1)
	{
		if (!(*name == *str))
			free(name);
		return (str);
	}
	new = ft_replace(str, name, find_var(&name[1]));
	free(str);
	free(name);
	return (expander(new, 0));
}

void	expander_args(t_cmd *list)
{
	t_token	*temp;
	char	*tmp_str;
	char	*s;

	while (list)
	{
		temp = list->tokens;
		while (temp)
		{
			if (temp->str[0] == '$')
				temp->str = dollar(temp->str);
			s = temp->str;
			if (!ft_strcmp(temp->str, "$") || !ft_strcmp(temp->str, "\"$\""))
				temp->str = remove_quotes(temp->str);
			else
			{
				tmp_str = expander(s, 0);
				temp->str = remove_quotes(tmp_str);
			}
			temp = temp->next;
		}
		list = list->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:31:20 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 15:18:45 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				return (free_ob(name, str));
			*start = index;
			if (str[index] == '$' && str[index + 1] == '?')
				return (free_ob(name, ft_strdup("$?")));
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
	char	*value;

	start = -1;
	name = malloc_ob(1024);
	name = expander2(str, name, &start, sep);
	if (start == -1)
	{
		if (!(*name == *str))
			free(name);
		return (str);
	}
	if (ft_strlen(name, 0) == 2 && ft_strcmp(name, "$?") == 0)
	{
		value = ft_itoa(g_terminal.status);
		new = ft_replace(str, name, value);
		free(value);
	}
	else
		new = ft_replace(str, name, find_var(&name[1]));
	free(str);
	free(name);
	return (expander(new, 0));
}

void	expander_args(t_cmd *list, int flag)
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
				temp->str = dollar(temp->str, &flag);
			s = temp->str;
			if (!flag && (!ft_strcmp(temp->str, "$") \
			|| !ft_strcmp(temp->str, "\"$\"")))
				temp->str = remove_quotes(temp->str);
			else if (!flag)
			{
				tmp_str = expander(s, 0);
				temp->str = remove_quotes(tmp_str);
			}
			temp = temp->next;
		}
		list = list->next;
	}
}

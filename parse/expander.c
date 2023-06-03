/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:31:20 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 17:58:54 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| (c >= '0' && c <= '9') || (c == '_'));
}

char	*find_needle(char *stack, char *needle)
{
	int		i;
	int		k;
	char	*new;
	char	*itoa;

	i = -1;
	if (!stack || !needle)
		return (stack);
	while (stack[++i])
	{
		//printf("char: %c\n", stack[i]);
		k = 0;
		while (stack[i + k] == needle[k] && needle[k] != '\0')
			k++;
		if (k == (int)ft_strlen(needle, 0))
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

char	*expander(char *str, char sep)
{
	char	*name;
	int		index;
	int		start;
	int		end;
	char	*new;

	start = -1;
	end = 0;
	index = 0;
	str = find_needle(str, "$?");
	name = malloc_ob(1024);
	while (str[index] && end == 0)
	{
		if (sep == 0 && (str[index] == '\'' || str[index] == '\"'))
			sep = str[index];
		else if (str[index] == sep)
			sep = 0;
		if (sep != '\'' && start == -1 && str[index] == '$')
		{
			if (!str[index + 1] || str[index + 1] == '.')
			{
				free(name);
				return (str);
			}
			start = index;
		}
		else if (start >= 0 && !check(str[index]) && ++end)
			name[index] = 0;
		if (end == 0 && start != -1)
			name[index - start] = str[index];
		index++;
	}
	if (start == -1)
	{
		free(name);
		return (str);
	}
	new = ft_replace(str, name, find_var(&name[1]));
	free(str);
	free(name);
	return (expander(new, 0));
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
	new[i++] = 0;
	free(temp);
	return (new);
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
			if (!ft_strcmp(temp->str, "$?"))
			{
				free(temp->str);
				temp->str = ft_itoa(g_terminal.status);
				return ;
			}
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

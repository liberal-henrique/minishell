/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:31:20 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/29 15:03:21 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| (c >= '0' && c <= '9') || (c == '_'));
}

char	*expander(char *str)
{
	char	name[1024];
	int		index;
	int		start;
	int		end;
	char	*new;

	start = -1;
	end = 0;
	index = 0;
	while (str[index] && end == 0)
	{
		if (start == -1 && str[index] == '$')
			start = index;
		else if (start >= 0 && !check(str[index]) && ++end)
			name[index] = 0;
		if (end == 0 && start != -1)
			name[index - start] = str[index];
		index++;
	}
	if (start == -1)
		return (str);
	new = ft_replace(str, name, find_var(&name[1]));
	free(str);
	return (expander(new));
}

char	*remove_quotes(char *str)
{
	char	*new;
	int		end;

	end = 0;
	if (*str == '\"')
		end = (ft_strlen(str, 0) - 1);
	else if (*str == '\'')
		end = (ft_strlen(str, 0) - 1);
	else
		return (str);
	new = ft_substring(str, 1, end);
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
				return ;
			s = temp->str;
			if (s && !(*s == '\'' && s[ft_strlen(s, 0) - 1] == '\''))
			{
				tmp_str = expander(s);
				temp->str = remove_quotes(tmp_str);
				//free(tmp_str);
			}	
			else if (s && (*s == '\'' && s[ft_strlen(s, 0) - 1] == '\''))
				temp->str = remove_quotes(s);
			//free(s);
			temp = temp->next;
		}
		list = list->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/04 15:22:05 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	separator_cmd(char **new, char **s, int *i, int j)
{
	*(*new)++ = (3 - *i);
	if ((*(*s) != '|') || *i || (*(*s)++ != '|'))
		*(*new)++ = *(*s)++;
	if (j == 2)
		*(*new)++ = *(*s)++;
	*(*new)++ = 2;
	*i = 1;
}

void	create_str(char *new, char *s, int i, char set)
{
	int	j;

	while (*s)
	{
		if (!set && is_quote(*s))
			set = *s;
		else if (set == *s && *s)
			set = 0;
		else if (!set && is_space(*s))
			(*s) = 2;
		if (!set && is_separator(s, &j))
			separator_cmd(&new, &s, &i, j);
		else
		{
			*new++ = *s++;
			i = 0;
		}
	}
	*new = 0;
}

t_cmd	*create_args(char *new)
{
	t_cmd	*begin;
	t_cmd	*end;
	char	**arr;
	int		i;

	i = -1;
	begin = NULL;
	end = NULL;
	arr = ft_split(new, 3);
	while (arr[++i])
		end = insert_end(&begin, arr[i], end);
	free(new);
	free_2d(arr);
	return (begin);
}

void	tokens(const char *line)
{
	t_cmd	*list;
	char	*new;

	list = NULL;
	new = malloc_ob(ft_strlen((char *)line) * 2);
	if (!new)
		return ;
	create_str(new, (char *)line, 0, 0);
	list = create_args(new);
	if (!list)
	{
		return ;
	}
	print_linked(list);
	deallocate(list);
}

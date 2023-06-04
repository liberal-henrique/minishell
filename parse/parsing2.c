/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 15:20:35 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	separator_cmd(char **new, char **s, int *i, int j)
{
	if (*(*s) == '|')
		*(*new)++ = (3 - *i);
	else
		*(*new)++ = 2;
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
	int	c;

	while (*s)
	{
		c = is_quote(*s);
		if (!set && c != 0)
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

int	is_separator_here(const char *s, int *j)
{
	if (s[0] == '>' && s[1] == '>')
		*j = (2);
	else if (s[0] == '<' && s[1] == '<')
		*j = (2);
	else if (s[0] == '>')
		*j = (3);
	else if (s[0] == '<')
		*j = (4);
	else if (s[0] == '|')
		*j = (5);
	else
		*j = 0;
	return (*j);
}

t_cmd	*create_list_tokens(char **arr)
{
	t_cmd	*begin;
	t_cmd	*end;
	t_cmd	*tmp;
	int		i;

	begin = NULL;
	end = NULL;
	i = -1;
	while (arr[++i])
		end = insert_end_tokens(&begin, arr[i], end);
	tmp = begin;
	while (tmp)
	{
		cmd_redirect(tmp, 0, 0);
		tmp = tmp->next;
	}
	return (begin);
}

t_cmd	*insert_end_tokens(t_cmd **root, char *s, t_cmd *end)
{
	t_cmd	*new_node;

	new_node = malloc_ob(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->pid = -1;
	ft_tokens(&new_node->tokens, s, -1);
	if (!(*root))
		*root = new_node;
	else
		end->next = new_node;
	return (new_node);
}

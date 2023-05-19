/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/19 15:18:48 by lliberal         ###   ########.fr       */
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

	while (*s)
	{
		if (!set && is_quote(*s))
			set = *s++;
		else if (set == *s && *s++ && g_terminal.fquotes++)
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

void	ft_phrases(const char *line)
{
	char	*new;
	char	**arr;
	t_cmd	*list;

	new = malloc_ob(ft_strlen((char *)line, 0) * 2);
	if (!new)
		return ;
	create_str(new, (char *)line, 0, 0);
	arr = ft_split(new, 3);
	list = create_list_tokens(arr);
	build_cmds_list(&list);
	// print_linked(list);
	g_terminal.begin = list;
	execute_main(list, 0);
	ft_wait(list);
	// list->flag_quotes = flag;
	free(new);
	free_2d(arr);
	deallocate(list);
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
		cmd_redirect(tmp);
		tmp = tmp->next;
	}
	return (begin);
}

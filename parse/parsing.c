/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/02 21:37:42 by lliberal         ###   ########.fr       */
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

// echo fudido >> outfile > out2 |                           <main.c wc > olafile
// echo ||
// echo |>
// echo >| --> error;
// ||

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

int	check_sintaxe(const char *s, char set, int i, int j)
{
	int	a;
	int	spa;
	int	g;

	spa = 0;
	g = 0;
	while (s && s[++i])
	{
		if (!is_quote(s[i]))
			a = s[i];
		else if (!is_quote(s[i]) && a == s[i])
			a = 0;
		else if (is_separator_here(s[spa], &g) != 0 && a == 0)
		{
			j = 1;
			spa = i + 1;
			if (g == 2)
				spa++;
			while (is_space(s[spa]))
				spa++;
			if ((g != 5 && is_separator_here(&s[spa], &g) != 0) \
			|| (g == 5 && s[spa] == '|'))
				return (1);
		}
	}
	if (j == 1 && !s[i])
		return (1);
	return (0);
}
// s[i] == '|'


int	ft_phrases(const char *line)
{
	char	*new2;
	char	**arr;
	t_cmd	*list;

	if (!line)
		return (STATUS_ERROR);
	if (check_sintaxe(line, 0, 0, 0) != 0)
	{
		write(2, "bash: syntax error near unexpected token 'newline'\n", 51);
		g_terminal.status = STATUS_ERROR;
		g_terminal.begin = NULL;
		return (g_terminal.status);
	}
	new2 = malloc_ob(ft_strlen(line, 0) * 10);
	create_str(new2, (char *)line, 0, 0);
	arr = ft_split(new2, 3);
	free(new2);
	list = create_list_tokens(arr);
	free_2d(arr);
	expander_args(list);
	build_cmds_list(&list);
	//print_linked(list);
	g_terminal.begin = list;
	execute_main(list, 0, -1);
	//printf("global childs%d\n", g_terminal.childs);
	// if (g_terminal.childs == 1)
	ft_wait(list);
	return (STATUS_SUCCESS);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 20:05:44 by lliberal         ###   ########.fr       */
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

int	check_sintaxe(const char *s, int spa, int i, int j)
{
	int	a;
	int	g;
	int	h;

	a = 0;
	while (is_space(s[++i]))
		;
	if (s[i] == '|')
		return (1);
	while (s && s[++i])
	{
		if (a == 0 && is_quote(s[i]) != 0)
			a = s[i];
		else if (is_quote(s[i]) != 0 && a == s[i])
			a = 0;
		if (is_separator_here(&s[i], &g) != 0 && a == 0)
		{
			j = 1;
			spa = i + 1;
			if (g == 2)
				spa++;
			while (is_space(s[spa]))
				spa++;
			if ((g != 5 && g != 0 && is_separator_here(&s[spa], &h) != 0) \
			|| (g == 5 && s[spa] == '|') || !s[spa])
				return (1);
			else
				j = 0;
		}
	}
	return (0);
}


int	ft_phrases(const char *line)
{
	char	*new2;
	char	**arr;

	if (!line)
		return (STATUS_ERROR);
	if (check_sintaxe(line, 0, -1, 0) != 0)
	{
		write(2, "bash: syntax error near unexpected token 'newline'\n", 51);
		g_terminal.status = STATUS_ERROR;
		g_terminal.list = NULL;
		return (g_terminal.status);
	}
	g_terminal.agoravai = 0;
	new2 = malloc_ob(ft_strlen(line, 0) * 10);
	create_str(new2, (char *)line, 0, 0);
	arr = ft_split(new2, 3);
	free(new2);
	g_terminal.list = create_list_tokens(arr);
	free_2d(arr);
	expander_args(g_terminal.list);
	build_cmds_list(&g_terminal.list, NULL);
	if (g_terminal.agoravai && cnt_here(g_terminal.list) > 1)
	{
		int fd[2];

		pipe(fd);
		char c[1];

		c[0] = 0;
		while (read(1, c, 1) > 0 && *c != '\n')
			;
		close(fd[1]);
		execute_main(g_terminal.list, fd[0], -1);
	}
	else
		execute_main(g_terminal.list, 0, -1);
	ft_wait(g_terminal.list);
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
		cmd_redirect(tmp, 0, 0, 0);
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

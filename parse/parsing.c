/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 16:18:33 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_sintaxe2(const char *s, int spa, int i, int j)
{
	int		g;
	int		h;
	int		a;

	a = 0;
	while (s && s[++i])
	{
		if (a == 0 && is_quote(s[i]) != 0)
			a = s[i];
		else if (is_quote(s[i]) != 0 && a == s[i])
			a = 0;
		if (is_separator_here(&s[i], &g) != 0 && a == 0)
		{
			j = 1;
			spa = i + 1 + (g == 2);
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

int	check_sintaxe(const char *s, int spa, int i, int j)
{
	int	k;

	while (is_space(s[++i]))
		;
	k = especial_case(s);
	if (k == 1 || k == 2)
		return (k);
	if (s[i] == '|')
		return (1);
	return (check_sintaxe2(s, spa, i, j));
}

int	macro_phrases(void)
{
	write(2, "bash: syntax error near unexpected token 'newline'\n", 51);
	g_terminal.status = STATUS_ERROR;
	g_terminal.list = NULL;
	return (g_terminal.status);
}

void	ft_phrases2(void)
{
	int		fd[2];
	char	c[1];

	if (g_terminal.agoravai && cnt_here(g_terminal.list) > 1)
	{
		pipe(fd);
		c[0] = 0;
		while (read(1, c, 1) > 0 && *c != '\n')
			;
		close(fd[1]);
		execute_main(g_terminal.list, fd[0], -1);
	}
	else
		execute_main(g_terminal.list, 0, -1);
	ft_wait(g_terminal.list);
}

int	ft_phrases(const char *line)
{
	char	*new2;
	char	**arr;
	int		k;

	if (!line)
		return (STATUS_ERROR);
	k = check_sintaxe(line, 0, -1, 0);
	if (k == 1)
		return (macro_phrases());
	else if (k == 2)
		return (STATUS_SUCCESS);
	g_terminal.agoravai = 0;
	new2 = malloc_ob(ft_strlen(line, 0) * 10);
	create_str(new2, (char *)line, 0, 0);
	arr = ft_split(new2, 3);
	free(new2);
	g_terminal.list = create_list_tokens(arr);
	free_2d(arr);
	expander_args(g_terminal.list, 0);
	build_cmds_list(&g_terminal.list, NULL);
	ft_phrases2();
	return (STATUS_SUCCESS);
}

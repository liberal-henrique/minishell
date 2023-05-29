/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:10:25 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/29 18:37:33 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_expo(t_expo *list)
{
	t_expo	*tmp;

	(void)tmp;
	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list->variable);
		free(list);
		list = tmp;
	}
	list = NULL;
}

void	clean_tokens(t_token *list)
{
	t_token	*tmp;

	(void)tmp;
	while (list)
	{
		tmp = list->next;
		free(list->str);
		free(list);
		list = tmp;
	}
	list = NULL;
}

void	cleanall(t_cmd *list, int f)
{
	if (f == 0)
		deallocate(list);
	if (f == 1)
	{
		free_2d(g_terminal.env);
		clean_expo(g_terminal.expo);
	}
	free(g_terminal.path);
}

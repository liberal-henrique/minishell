/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:10:25 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/28 22:08:53 by lliberal         ###   ########.fr       */
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

void	cleanall(t_cmd *list)
{
	/* t_cmd	*tmp;

	tmp = list;
	while (tmp)
	{
		deallocate(list);
		tmp = tmp->next;
	} */
	deallocate(list);
	free_2d(g_terminal.env);
	clean_expo(g_terminal.expo);
	free(g_terminal.path);
	//clean_tokens(list->tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:49:49 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/28 23:16:10 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	token_add_back(t_token **root, char *str)
{
	t_token	*new_node;
	t_token	*tmp;

	tmp = *root;
	new_node = malloc_ob(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->next = NULL;

	new_node->str = str;
	printf("2: %p\n", new_node->str);
	if (!(*root))
		*root = new_node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	ft_tokens(t_token **token, char *phrase)
{
	char	**tokens;
	int		i;

	tokens = ft_split(phrase, 2);
	i = -1;
	while (tokens[++i])
	{
		printf("1: %p\n", tokens[i]);
		token_add_back(token, tokens[i]);
	}
	free(tokens);
	// free(phrase);
	//free_2d(tokens);
}

void	token_remove(t_token **root, t_token *elem)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *root;
	if (tmp == elem)
	{
		tmp = (*root)->next;
		free((*root)->str);
		free(*root);
		*root = tmp;
		return ;
	}
	while (tmp)
	{
		if (tmp->next == elem)
		{
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp2->str);
			free(tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}

void	token_print(t_token *curr)
{
	while (curr)
	{
		printf("Token: %s\n", curr->str);
		curr = curr->next;
	}
}

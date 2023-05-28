/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:14:40 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/28 23:12:42 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cnt_rec(t_token *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt_rec(node->next));
}

void	clean_list_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	while (token)
	{
		tmp = token->next;
		free(token->str);
		printf("3: %p\n", token->str);
		free(token);
		token = tmp;
	}
}

void	deallocate(t_cmd *curr)
{
	t_cmd	*temp;

	temp = NULL;
	while (curr)
	{
		H;
		temp = curr->next;
		clean_list_tokens(curr->tokens);
		free_2d(curr->args);
		free(curr->gpath);
		free(curr);
		curr = temp;
	}
}

void	*get_function(char *name)
{
	(void) name;
	if (ft_compare("echo", name))
		return (execute_echo);
	if (ft_compare("pwd", name))
		return (execute_pwd);
	return (execute_default);
}

void	print_linked(t_cmd *curr)
{
	int	i;

	// printf("+++++++++++++++++++++++++++++++++++++++\n");
	while (curr)
	{
		// printf("------------------------------------\n");
		i = -1;
		token_print(curr->tokens);
		while (curr->args[++i])
			printf("Argumento: %i, %s\n", i, curr->args[i]);
		// printf("path: %s\n", curr->gpath);
		// printf("fd_master[0]: %i\n", curr->fd_master[0]);
		// printf("fd_master[1]: %i\n", curr->fd_master[1]);
		curr = curr->next;
	}
}

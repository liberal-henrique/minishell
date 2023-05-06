/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:14:40 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/06 18:08:09 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cnt_rec(t_cmd *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt_rec(node->next));
}

void	deallocate(t_cmd *curr)
{
	t_cmd	*temp;

	temp = NULL;
	while (curr)
	{
		temp = curr->next;
		free_2d(curr->args);
		free(curr->gpath);
		free(curr);
		curr = temp;
	}
}

t_cmd	*insert_end(t_cmd **root, char *s, t_cmd *end)
{
	t_cmd	*new_node;

	new_node = malloc_ob(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->args = ft_split(s, 2);
	new_node->gpath = get_gpath(g_terminal.env, new_node->args);
	pipe(new_node->fd);
	if (!(*root))
		*root = new_node;
	else
		end->next = new_node;
	return (new_node);
}

void	print_linked(t_cmd *curr)
{
	int	i;

	printf("+++++++++++++++++++++++++++++++++++++++\n");
	while (curr)
	{
		printf("------------------------------------\n");
		i = -1;
		while (curr->args[++i])
			printf("%s\n", curr->args[i]);
		printf("path: %s\n", curr->gpath);
		curr = curr->next;
	}
}

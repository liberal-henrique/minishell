/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:14:40 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/04 15:19:01 by lliberal         ###   ########.fr       */
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

void	*get_function(char *name)
{
	(void) name;
	// if (ft_compare("echo", name))
	// 	return (execute_echo);
	// if (ft_compare(">", name))
	// 	return (execute_redirection_out);
	// if (ft_compare("env", name))
	// 	return (execute_env);
	// if (ft_compare(">>", name))
	// 	return (execute_redirection_append_out);
	return (execute_default);
}

t_cmd	*insert_end(t_cmd **root, char *s, t_cmd *end)
{
	t_cmd	*new_node;

	new_node = malloc_ob(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->args = ft_split(s, 2);
	new_node->execute = get_function(new_node->args[0]);
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

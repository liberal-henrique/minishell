/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:23:21 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 21:25:24 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap_content(char **node, char **node1)
{
	char	*tmp;

	tmp = *node;
	*node = *node1;
	*node1 = tmp;
}

void	bubblesort(t_expo *root)
{
	t_expo	*ptr;
	int		swapped;

	swapped = 1;
	while (1)
	{
		ptr = root;
		swapped = 0;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->variable, ptr->next->variable) > 0)
			{
				swap_content(&ptr->variable, &ptr->next->variable);
				swap_content(&ptr->value, &ptr->next->value);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		if (swapped == 0)
			break ;
	}
}

char	*put_quotes(char *str)
{
	char	*new;
	int		i;

	i = 1;
	new = malloc(ft_strlen(str, 0) + 2);
	if (!new)
		return (NULL);
	new[0] = '\"';
	while (*str)
		new[i++] = *str++;
	new[i] = '\"';
	return (new);
}

t_expo	*insert_end_expo_list(t_expo **root, char *s, t_expo **end)
{
	t_expo	*new_node;

	new_node = malloc_ob(sizeof(t_expo));
	if (!new_node)
		return (NULL);
	new_node->variable = ft_substring(s, 0, ft_strlen(s, '=') + 1);
	new_node->value = ft_substring(s, (ft_strlen(s, '=') + 1), ft_strlen(s, 0));
	if (!(*root))
	{
		*root = new_node;
		*end = new_node;
	}
	else
	{
		(*end)->next = new_node;
		*end = new_node;
	}
	return (new_node);
}

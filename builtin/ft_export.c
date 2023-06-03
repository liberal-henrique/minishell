/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:01:23 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 21:04:06 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_expo	*create_expo(char **env)
{
	t_expo	*begin;
	t_expo	*end;
	int		i;

	begin = NULL;
	end = NULL;
	i = -1;
	while (env[++i])
		end = insert_end_expo_list(&begin, env[i], &end);
	bubblesort(begin);
	return (begin);
}

int	export_variable_name(char *cmd)
{
	size_t	i;

	i = -1;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_' )
		return (STATUS_ERROR);
	if (cmd[0] == '_' && cmd[1] == '=')
		return (STATUS_ERROR);
	while (cmd[++i])
	{
		if (!ft_isalpha(cmd[i]) && !ft_isnum(cmd[i]) && cmd[i] != '_')
			return (STATUS_ERROR);
		if (cmd[i + 1] == '=')
			return (STATUS_SUCCESS);
	}
	return (STATUS_SUCCESS);
}

void	insert_end_list(t_expo **root, char *value)
{
	t_expo	*new_node;
	t_expo	*tmp;

	tmp = *root;
	new_node = malloc(sizeof(t_expo));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->variable = ft_substring(value, 0, (ft_strlen(value, '=') + 1));
	new_node->value = ft_substring(value, (ft_strlen(value, '=') + 1), \
	ft_strlen(value, 0));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

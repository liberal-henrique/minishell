/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:01:23 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/17 22:04:17 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_variable_replaced(char *cmd, int flag)
{
	t_expo	*tmp;
	size_t		len_variable;
	size_t		len_name;

	len_variable = 0;
	len_name = ft_strlen(cmd, '=');
	tmp = g_terminal.expo;
	while (tmp && cmd)
	{
		if (ft_strlen(tmp->variable, '=') > len_name)
			len_variable = ft_strlen(tmp->variable, '=');
		else
			len_variable = len_name;
		if (ft_strncmp(tmp->variable, cmd, len_name) == 0)
		{
			tmp->variable = ft_replace(tmp->variable, tmp->variable, \
			ft_substring(cmd, 0, ft_strlen(cmd, '=')));
			tmp->value = ft_replace(tmp->value, tmp->value, \
			ft_substring(cmd, (ft_strlen(cmd, '=') + 1), ft_strlen(cmd, 0)));
			flag += 1;
		}
		tmp = tmp->next;
	}
	return (flag);
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
	new_node->variable = ft_substring(value, 0, ft_strlen(value, '='));
	new_node->value = ft_substring(value, (ft_strlen(value, '=') + 1), ft_strlen(value, 0));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

int	execute_export(t_cmd *cmd)
{
	int	flag;

	flag = 0;
	if (!cmd->args[1])
	{
		print_list(g_terminal.expo);
		return (STATUS_SUCCESS);
	}
	flag = env_variable_replaced(cmd->args[1], 0);
	if (flag == 0)
	{
		insert_end_list(&g_terminal.expo, cmd->args[1]);
		g_terminal.env = synchronize_env(g_terminal.env, cmd->args[1]);
	}
	return (STATUS_SUCCESS);
}

t_expo	*create_expo(char **env)
{
	t_expo	*begin;
	t_expo	*end;
	int		i;

	begin = NULL;
	end = NULL;
	i = 0;
	while (env[++i])
		end = insert_end_expo_list(&begin, env[i], &end);
	// g_terminal.end = end;
	bubblesort(begin);
	return (begin);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:01:23 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 21:17:19 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_variable_replaced2(char *cmd, int *flag, t_expo *tmp)
{
	size_t		len_variable;
	char		*sub;
	t_expo		helper;

	while (tmp && cmd)
	{
		len_variable = ft_strlen(tmp->variable, 0);
		if (ft_strncmp(tmp->variable, cmd, len_variable) == 0)
		{
			helper = *tmp;
			sub = ft_substring(cmd, 0, (ft_strlen(cmd, '=') + 1));
			tmp->variable = ft_replace(tmp->variable, tmp->variable, sub);
			free(helper.variable);
			free(sub);
			sub = ft_substring(cmd, (ft_strlen(cmd, '=') + 1), \
			ft_strlen(cmd, 0));
			tmp->value = ft_strdup(sub);
			free(helper.value);
			free(sub);
			*flag = 1;
		}
		tmp = tmp->next;
	}
}

int	env_variable_replaced(char *cmd, int *flag)
{
	t_expo		*tmp;

	tmp = g_terminal.expo;
	*flag = 0;
	if (export_variable_name(cmd) != 0)
	{
		write(2, "Not a valid identifier\n", 23);
		*flag = -2;
		return (STATUS_ERROR);
	}
	env_variable_replaced2(cmd, flag, tmp);
	return (0);
}

void	execute_export_2(t_cmd *cmd, int i)
{
	int	flag;

	while (cmd->args[i])
	{
		flag = 0;
		if (env_variable_replaced(cmd->args[i], &flag) == 1)
			cmd->status = STATUS_ERROR;
		if (flag != 0 && flag != -2)
			if (cmd->args[i][ft_strlen(cmd->args[i], '=')] == '=')
				g_terminal.env = sync_e(cmd->args[i], -1, 0);
		if (flag == 0 && flag != -2)
		{
			insert_end_list(&g_terminal.expo, cmd->args[i]);
			if (cmd->args[i][ft_strlen(cmd->args[i], '=')] == '=')
				g_terminal.env = syncadd(g_terminal.env, cmd->args[i]);
		}
		i++;
	}
}

int	execute_export(t_cmd *cmd)
{
	if (cmd->args[1] && cmd->next)
		return (0);
	if (!cmd->args[1])
	{
		if (!cmd->next)
			print_list(g_terminal.expo);
		else
			print_list2(g_terminal.expo, cmd);
		cmd->status = STATUS_SUCCESS;
		return (cmd->status);
	}
	execute_export_2(cmd, 1);
	return (cmd->status);
}

char	*find_var(char *var)
{
	t_expo		*tmp;
	size_t		len_var;

	tmp = g_terminal.expo;
	len_var = 0;
	while (tmp)
	{
		len_var = ft_strlen(tmp->variable, '=');
		if (ft_strlen(var, 0) == len_var \
		&& ft_strncmp(tmp->variable, var, len_var) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

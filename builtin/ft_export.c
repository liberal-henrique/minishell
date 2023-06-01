/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:01:23 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/01 16:25:22 by lliberal         ###   ########.fr       */
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

void	is_wrong(void)
{
	printf("Not a valid identifier\n");
	// Aqui devemos encaminhar uma mensagem de erro
}

int	export_variable_name(char *cmd)
{
	size_t	i;

	i = -1;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_' )
	{
		return (STATUS_ERROR);
	}
	if (cmd[0] == '_' && cmd[1] == '=')
	{
		return (STATUS_ERROR);
	}
	while (cmd[++i])
	{
		if (!ft_isalpha(cmd[i]) && !ft_isnum(cmd[i]) && cmd[i] != '_')
		{
			return (STATUS_ERROR);
		}
		if (cmd[i + 1] == '=')
		{

			return (STATUS_SUCCESS);
		}
	}
	return (STATUS_SUCCESS);
}

int	env_variable_replaced(char *cmd, int *flag)
{
	char		*sub;
	size_t		len_variable;
	size_t		len_name;
	t_expo		*tmp;
	t_expo		helper;

	len_variable = 0;
	len_name = ft_strlen(cmd, '=');
	tmp = g_terminal.expo;
	*flag = 0;
	if (export_variable_name(cmd) != 0)
	{
		// printf("Not a valid identifier\n");
		write(2, "Not a valid identifier\n", 23);
		*flag = -2;
		return (STATUS_ERROR);
	}
	while (tmp && cmd)
	{
		if ((ft_strlen(tmp->variable, '=')) > len_name)
			len_variable = ft_strlen(tmp->variable, '=');
		else
			len_variable = len_name;
		if (ft_strncmp(tmp->variable, cmd, len_variable) == 0)
		{
			helper = *tmp;
			sub = ft_substring(cmd, 0, (ft_strlen(cmd, '=') + 1));
			tmp->variable = ft_replace(tmp->variable, tmp->variable, sub);
			free(helper.variable);
			free(sub);
			sub = NULL;
			sub = ft_substring(cmd, (ft_strlen(cmd, '=') + 1), ft_strlen(cmd, 0));
			tmp->value = ft_strdup(sub);
			free(helper.value);
			free(sub);
			*flag = 1;
		}
		tmp = tmp->next;
	}
	/* return (*flag); */
	return (0);
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
	new_node->value = ft_substring(value, (ft_strlen(value, '=') + 1), ft_strlen(value, 0));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

int	execute_export(t_cmd *cmd)
{
	int	flag;
	int	i;

	i = 1;
	if (!cmd->args[1])
	{
		if (!cmd->next)
			print_list(g_terminal.expo);
		else
			print_list2(g_terminal.expo, cmd);
		g_terminal.status = STATUS_SUCCESS;
		return (g_terminal.status);
	}
	else
	{
		while (cmd->args[i])
		{
			if (env_variable_replaced(cmd->args[i], &flag) == 1)
			{
				g_terminal.status = STATUS_ERROR;
				//return (g_terminal.status);
			}
			if (flag != 0 && flag != -2)
				if (cmd->args[i][ft_strlen(cmd->args[i], '=')] == '=')
					g_terminal.env = synchronize_env(cmd->args[i]);
			if (flag == 0 && flag != -2)
			{
				insert_end_list(&g_terminal.expo, cmd->args[i]);
				if (cmd->args[i][ft_strlen(cmd->args[i], '=')] == '=')
					g_terminal.env = synchronize_env_adding(g_terminal.env, cmd->args[i]);
			}
			i++;
		}
	}
	/* if (g_terminal.status == S)
	g_terminal.status = STATUS_SUCCESS; */
	return (g_terminal.status);
}

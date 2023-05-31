/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:49:48 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/31 15:49:07 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**destroy_row(char **env, char *str)
{
	char	**new;
	int		i;
	int		i_c;
	int 	k;

	new = malloc_ob(sizeof(char *) * (ft_strlen_2d(env)));
	i = 0;
	i_c = 0;
	k = ft_strlen_2d(env);
	while (i_c < k && env[i])
	{
		/* if (ft_strncmp(env[i], str, (ft_strlen(env[i], '='))) != 0)
		{
			new[i_c] = ft_strdup(env[i]);
			i_c++;
			i++;
		} */
		if (!(ft_strncmp(env[i], str, ft_strlen(env[i], '=')) == 0 && ft_strlen(str, 0) == ft_strlen(env[i], '=')))
		{
			new[i_c] = ft_strdup(env[i]);
			i_c++;
			i++;
		}
		else
			i++;
	}
	free_2d(env);
	return (new);
}

void	destroy_first_node(t_expo **list)
{
	t_expo	*tmp;

	tmp = (*list);
	(*list) = (*list)->next;
	free(tmp);
	free(tmp->variable);
	free(tmp->value);
	tmp = NULL;
}


//if (ft_strncmp(g_terminal.env[length], cmd->args[i], ft_strlen(g_terminal.env[length], '=')) == 0 && ft_strlen(cmd->args[i], 0) == ft_strlen(g_terminal.env[length], '='))

void	destroy_node(t_expo **list, char *str)
{
	t_expo	*tmp;
	t_expo	*aux;
	size_t	len;
	int		i;

	i = 0;
	tmp = (*list);
	len = ft_strlen((*list)->variable, '=');
	/* if (ft_strncmp((*list)->variable, str, len) == 0)
	{
		destroy_first_node(list);
		return ;
	} */
	if (ft_strncmp((*list)->variable, str, ft_strlen((*list)->variable, '=')) == 0 && ft_strlen(str, 0) == ft_strlen((*list)->variable, '='))
	{
		destroy_first_node(list);
		return ;
	}
	//printf("arg: %s\n", str);
	while (tmp->next)
	{
		//printf("var :%s\n", (*list)->variable);
		if (ft_strncmp(tmp->next->variable, str, ft_strlen(tmp->next->variable, '=')) == 0 && ft_strlen(str, 0) == ft_strlen(tmp->next->variable, '='))
		{
			aux = tmp->next;
			if (tmp->next)
				tmp->next = tmp->next->next;
			free(aux->variable);
			free(aux->value);
			free(aux);
			tmp = NULL;
			return ;
		}
		else
			tmp = tmp->next;
	}
}

		/* if (ft_strncmp(tmp->next->variable, str, len) == 0)
		{
			aux = tmp->next;
			if (tmp->next)
				tmp->next = tmp->next->next;
			free(aux->variable);
			free(aux->value);
			free(aux);
			aux = NULL;
			return ;
		} */

int	cnt(t_expo *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt(node->next));
}

int	execute_unset(t_cmd *cmd)
{
	int		len_variable;
	int		length;
	int		i;

	i = 1;
	length = -1;
	len_variable = 0;
	while (g_terminal.env[++length] && cmd->args[i])
	{
		//len_variable = ft_strlen(g_terminal.env[length], '=');
		if (ft_strncmp(g_terminal.env[length], cmd->args[i], ft_strlen(g_terminal.env[length], '=')) == 0 && ft_strlen(cmd->args[i], 0) == ft_strlen(g_terminal.env[length], '='))
		{
			printf("var: %s\n", g_terminal.env[length]);
			printf("arg: %s\n", cmd->args[i]);
			g_terminal.env = destroy_row(g_terminal.env, cmd->args[i]);
			destroy_node(&g_terminal.expo, cmd->args[i]);
			if (cmd->args[i + 1])
			{
				length = -1;
				i++;
			}
			else
				break ;
			length = -1;
		}
	}
	return (STATUS_SUCCESS);
}

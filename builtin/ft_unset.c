/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:49:48 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/26 11:41:46 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**destroy_row(char **env, char *str)
{
	//printf("old_env %i\n", ft_strlen_2d(env));
	//printf("str: %s\n", str);
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
		//printf("i_c: %i\n", i_c);
		if (ft_strncmp(env[i], str, (ft_strlen(env[i], '='))) != 0)
		{
			//printf("i_c %d\n", i_c);
			//printf("i %d\n", i);
			new[i_c] = ft_strdup(env[i]);
			i_c++;
			i++;
		}
		else
			i++;
	}
	free_2d(env);
	//printf("new_env %i\n", ft_strlen_2d(new));
	return (new);
}

void	destroy_first_node(t_expo **list)
{
	t_expo	*tmp;

	tmp = (*list);
	(*list) = (*list)->next;
	free(tmp);
	tmp = NULL;
}

void	destroy_node(t_expo **list, char *str)
{
	//printf("str: %s\n", str);
	t_expo	*tmp;
	t_expo	*aux;
	size_t	len;
	int		i;

	i = 0;
	tmp = (*list);
	len = ft_strlen((*list)->variable, '=');
	if (ft_strncmp((*list)->variable, str, len) == 0)
	{
		destroy_first_node(list);
		return ;
	}
	while (tmp->next)
	{
		len = ft_strlen(tmp->next->variable, '=');
		if (ft_strncmp(tmp->next->variable, str, len) == 0)
		{
			//H;
			aux = tmp->next;
			if (tmp->next)
				tmp->next = tmp->next->next;
			free(aux);
			aux = NULL;
			//tmp = (*list);
			return ;
		}
		else
			tmp = tmp->next;
	}
}

int	cnt(t_expo *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt(node->next));
}

// export a=1 b=2 c=3 d=4 e=5
// unset a b c d e
int	execute_unset(t_cmd *cmd)
{
	int		len_variable;
	int		length;
	int		i;

	i = 1;
	length = -1;
	len_variable = 0;
	//printf("Env1 %i\n", ft_strlen_2d(g_terminal.env));
	while (g_terminal.env[++length] && cmd->args[i])
	{
		//printf("arg: %s\n", cmd->args[3]);
		//printf("i: %i\n", i);
		len_variable = ft_strlen(g_terminal.env[length], '=');
		if (ft_strncmp(g_terminal.env[length], cmd->args[i], len_variable) == 0 \
		&& g_terminal.env[length][len_variable] == '=')
		{
			//H;
			//printf("Env2 %i\n", ft_strlen_2d(g_terminal.env));
			g_terminal.env = destroy_row(g_terminal.env, cmd->args[i]);
			//printf("Env3 %i\n", ft_strlen_2d(g_terminal.env));
			destroy_node(&g_terminal.expo, cmd->args[i]);
			if (cmd->args[i + 1])
			{
				//H;
				length = -1;
				i++;
			}
			else
			{
				//T;
				break ;
			}
			length = -1;
		}
		//printf("Env %i\n", ft_strlen_2d(g_terminal.env));
		//printf("Expo %i\n", cnt(g_terminal.expo));
	}
	return (STATUS_SUCCESS);
}

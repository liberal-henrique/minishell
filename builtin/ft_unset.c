/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:49:48 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/17 23:05:05 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Ainda esta em testes. Ja consigo apagar a variavel contudo
// acredito que seja legal criar um novo array_2d menor sem essa
// string especifica
int	execute_unset(t_cmd *cmd)
{

	int		length;
	size_t	len_name;
	int		len_variable;

	length = -1;
	len_name = ft_strlen(cmd->args[1], '=');
	len_variable = 0;
	while (g_terminal.env[++length] && cmd->args[1])
	{
		if (ft_strlen(g_terminal.env[length], '=') > len_name)
			len_variable = ft_strlen(g_terminal.env[length], '=');
		else
			len_variable = len_name;
		if (ft_strncmp(g_terminal.env[length], cmd->args[1], len_variable) == 0)
		{
			g_terminal.env[length] = ft_strdup("esvaziar");
			free(g_terminal.env[length]);
		}
	}
	return (STATUS_SUCCESS);
}

// int	execute_unset(t_cmd *cmd)
// {
// 	t_expo	*tmp;
// 	size_t	length;
// 	int		len_variable;

// 	len_variable = 0;
// 	g_terminal.expo = tmp;
// 	length = ft_strlen(cmd->args[1], '=');
// 	while (tmp)
// 	{
// 		if (ft_strlen(tmp->variable, '=') > length)
// 			len_variable = ft_strlen(tmp->variable, '=');
// 		else
// 			len_variable = length;
// 		if (ft_strncmp(tmp->variable, cmd->args[1], len_variable) == 0)
// 		{
// 			tmp->variable = NULL;
// 			free(tmp->variable);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (STATUS_SUCCESS);
// }

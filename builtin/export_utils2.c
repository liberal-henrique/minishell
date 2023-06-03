/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:23:21 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 21:24:59 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_expo *node)
{
	t_expo	*tmp;

	tmp = node;
	while (tmp)
	{
		printf("declare -x ");
		printf("%s", tmp->variable);
		if (tmp->value)
		{
			printf("\"");
			printf("%s", tmp->value);
			printf("\"");
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	print_list2(t_expo *node, t_cmd *cmd)
{
	int	fd[2];

	pipe(fd);
	while (node)
	{
		write(fd[1], "declare -x ", ft_strlen("declare -x ", 0));
		write(fd[1], node->variable, ft_strlen(node->variable, '='));
		write(fd[1], "=", 1);
		write(fd[1], "\"", 1);
		write(fd[1], node->value, ft_strlen(node->value, 0));
		write(fd[1], "\"", 1);
		write(fd[1], "\n", 1);
		node = node->next;
	}
	close(fd[1]);
	cmd->next->fd_master[0] = fd[0];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:39:12 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/24 17:12:19 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_oldpwd(char *new)
{
	t_expo	*tmp;
	int			len_var;

	tmp = g_terminal.expo;
	while (tmp)
	{
		len_var = ft_strlen(tmp->value, 0) - (ft_strlen(tmp->value, '=') + 1);
		if (ft_strncmp(tmp->value, new, len_var) == 0 && tmp->value[len_var] == '=')
		{

		}
		tmp = tmp->next;
	}
}

int	execute_cd(t_cmd *cmd)
{
	char	*str;
	char	*cwd;

	cwd = find_var("PWD");
	str = NULL;
	if (!ft_strncmp(cmd->args[1], cwd, ft_strlen(cwd, 0)))
	{
		if (chdir(cmd->args[1]) != 0)
			return (STATUS_ERROR);
		return (STATUS_SUCCESS);
	}
	str = str_join(cwd, cmd->args[1], '/');
	if (chdir(str) != 0)
	{
		free(str);
		return (STATUS_ERROR);
	}
	free(str);
	return (STATUS_SUCCESS);
}

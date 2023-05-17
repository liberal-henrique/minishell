/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:39:12 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/10 15:17:04 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_cd(t_cmd *cmd)
{
	char	*str;
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * 1024);
	getcwd(cwd, 1024);
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
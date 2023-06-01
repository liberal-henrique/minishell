/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:30:26 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/01 11:47:16 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int	execute_pwd(t_cmd *cmd)
{
    char *cwd;

	(void) cmd;
    //cwd = (char *)malloc(sizeof(char) * 1024);
    cwd = find_var("PWD");
    if (cwd)
	{
		write(1, cwd, ft_strlen(cwd, 0));
		write(1, "\n", 1);
        free(cwd);
	}
    else
    {
        perror("Error on getcwd\n");
        return (STATUS_ERROR);
    }
	return (STATUS_SUCCESS);
}
 */

int	execute_pwd(t_cmd *cmd)
{
	char	*cwd;

	(void) cmd;
	cwd = malloc_ob(1024);
	if (getcwd(cwd, 1024) != NULL)
	{
		write(1, cwd, ft_strlen(cwd, 0));
		write(1, "\n", 1);
	}
	else
	{
		perror("Error on getcwd\n");
		g_terminal.status = STATUS_ERROR;
		return (g_terminal.status);
	}
	free(cwd);
	return (STATUS_SUCCESS);
}

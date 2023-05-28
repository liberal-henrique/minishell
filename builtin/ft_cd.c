/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:39:12 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/28 18:27:04 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_oldpwd(char *new)
{
	int	flag;
	char *str;

	flag = 0;
	str = str_join("OLDPWD", new, '=');
	env_variable_replaced(str, &flag);
	g_terminal.env = synchronize_env(str);
}

void	update_pwd(char *new)
{
	char	*str;
	int 	flag;
	int		i;

	i = 0;
	flag = 0;
	i = ft_strlen(new, 0);
	while (new[--i] != '/')
		;
	--i;
	while (new[--i] != '/')
		;
	if (new[ft_strlen(new, 0) - 1] == '.' && new[ft_strlen(new, 0) - 2] == '.')
		str = str_join("PWD", ft_substring(new, 0, i), '=');
	else
		str = str_join("PWD", new, '=');
	env_variable_replaced(str, &flag);
	g_terminal.env = synchronize_env(str);
}

void	update_paths(char *cwd, char *arg, int f)
{
	if (f == 1)
	{
		update_oldpwd(cwd);
		update_pwd(arg);
	}
	else if (f == 2)
	{
		update_oldpwd(cwd);
		update_pwd(str_join(cwd, arg, '/'));
	}
}

int	execute_cd(t_cmd *cmd)
{
	char	*str;
	char	*cwd;

	str = NULL;
	cwd = find_var("PWD");
	if (!ft_strncmp(cmd->args[1], cwd, ft_strlen(cwd, 0)))
	{
		if (chdir(cmd->args[1]) != 0)
			return (STATUS_ERROR);
		update_paths(cwd, cmd->args[1], 1);
		return (STATUS_SUCCESS);
	}
	str = str_join(cwd, cmd->args[1], '/');
	if (chdir(str) != 0)
	{
		free(str);
		printf("%s%s%s\n", "bash: cd: ", cmd->args[1], ": No such file or directory");
		return (STATUS_ERROR);
	}
	free(str);
	update_paths(cwd, cmd->args[1], 2);
	return (STATUS_SUCCESS);
}

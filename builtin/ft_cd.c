/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:39:12 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 15:25:59 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_oldpwd(char *new)
{
	char	*str;
	int		flag;

	flag = 0;
	str = str_join("OLDPWD", new, '=');
	env_variable_replaced(str, &flag);
	g_terminal.env = sync_e(str, -1, 0);
	free(str);
}

void	update_pwd(char *new)
{
	char	*str;
	char	*sub;
	int		flag;
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
	{
		sub = ft_substring(new, 0, i);
		str = str_join("PWD", sub, '=');
		free(sub);
	}
	else
		str = str_join("PWD", new, '=');
	env_variable_replaced(str, &flag);
	g_terminal.env = sync_e(str, -1, 0);
	free(str);
	free(new);
}

void	update_paths(char *cwd, char *arg, int f)
{
	char	*dup;

	if (f == 1)
	{
		dup = ft_strdup(arg);
		update_pwd(dup);
		update_oldpwd(cwd);
	}
	else if (f == 2)
	{
		update_pwd(str_join(cwd, arg, '/'));
		update_oldpwd(cwd);
	}
}

int	execute_cd_2(t_cmd *cmd, char *cwd)
{
	char	*str;

	if (chdir(cmd->args[1]) == 0)
		str = ft_strdup(cmd->args[1]);
	else
	{
		str = str_join(cwd, cmd->args[1], '/');
		if (chdir(str) != 0)
		{
			free(str);
			write(2, "bash: cd: ", 10);
			write(2, cmd->args[1], ft_strlen(cmd->args[1], 0));
			write(2, ": No such file or directory\n", 28);
			free(cwd);
			cmd->status = STATUS_ERROR;
			return (cmd->status);
		}
	}
	update_paths(cwd, cmd->args[1], 2);
	free(str);
	free(cwd);
	cmd->status = STATUS_SUCCESS;
	return (cmd->status);
}

int	execute_cd(t_cmd *cmd)
{
	char	*cwd;

	if (cmd->args[2] && write(2, "bash: cd: too many arguments\n", 29))
		return (status(cmd, STATUS_ERROR));
	cwd = getcwd(NULL, 0);
	if (ft_compare(cmd->args[1], "-"))
	{
		if (chdir(find_var("OLDPWD")) != 0)
			return (status(cmd, STATUS_ERROR));
		update_paths(cwd, find_var("OLDPWD"), 1);
		free(cwd);
		cmd->status = STATUS_SUCCESS;
		return (cmd->status);
	}
	else if (!ft_strncmp(cmd->args[1], cwd, ft_strlen(cwd, 0)))
	{
		printf("%s\n", cmd->args[1]);
		if (chdir(cmd->args[1]) != 0)
			return (status(cmd, STATUS_ERROR));
		update_paths(cwd, cmd->args[1], 1);
		free(cwd);
		return (status(cmd, STATUS_SUCCESS));
	}
	return (execute_cd_2(cmd, cwd));
}

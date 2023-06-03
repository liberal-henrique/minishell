/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:34:24 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/03 17:55:12 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

char	**create_array_cmds(t_token *list)
{
	t_token	*tmp;
	char	**args;
	int		length;
	int		i;

	i = 0;
	tmp = list;
	length = cnt_rec(list) + 1;
	args = malloc_ob(sizeof(char *) * length);
	if (!args)
		return (NULL);
	while (tmp)
	{
		args[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	return (args);
}

void	build_cmds_list(t_cmd **list)
{
	t_cmd	*tmp;

	tmp = (*list);
	if (!(*list))
		return ;
	while (tmp)
	{
		tmp->args = create_array_cmds(tmp->tokens);
		if (!tmp->args[0])
		{
			tmp->stop = 1;
			tmp = tmp->next;
			g_terminal.agoravai = 1;
		}
		else
		{
			tmp->execute = get_function(tmp->args[0]);
			tmp->gpath = get_gpath(g_terminal.env, tmp->args);
			tmp->is_type = 0;
			if (tmp->gpath && ((tmp->args[0][0] == '/') \
			|| !ft_strncmp("./", tmp->args[0], 2)))
			{
				tmp->is_type = (access(tmp->gpath, X_OK) != 0);
				if (tmp->is_type == 0)
					tmp->is_type = 2;
			}
			if (tmp->next)
				pipe(tmp->fd);
			else
				tmp->fd[1] = 1;
			tmp = tmp->next;
		}

	}
}

void	cmd_redirect(t_cmd *cmd)
{
	t_token	*tmp;
	int		f;
	int		i;
	int		fd;

	tmp = cmd->tokens;
	i = 0;
	fd = 0;
	while (tmp)
	{
		f = is_redirect(tmp->str);
		if (f == 1)
		{
			tmp->next->str = remove_quotes(tmp->next->str);
			fd = open(tmp->next->str, O_RDONLY, 0444);
			if (fd == -1)
			{
				write(2, "bash: ", 6);
				write(2, tmp->next->str, ft_strlen(tmp->next->str, 0));
				write(2, ": No such file or directory\n", 28);
				cmd->status = 1;
				cmd->stop = 1;
				close(fd);
				return ;
			}
			cmd->fd_master[0] = fd;
		}
		else if (f == 2)
		{
			tmp->next->str = remove_quotes(tmp->next->str);
			fd = open(tmp->next->str, O_CREAT | O_TRUNC | O_RDWR, 0644);
			if (fd == -1)
			{
				write(2, "bash: ", 6);
				write(2, tmp->next->str, ft_strlen(tmp->next->str, 0));
				write(2, ": No such file or directory\n", 28);
				cmd->status = 1;
				cmd->stop = 1;
				close(fd);
				return ;
			}
			cmd->fd_master[1] = fd;
		}
		else if (f == 4)
		{
			tmp->next->str = remove_quotes(tmp->next->str);
			fd = open(tmp->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				write(2, "bash: ", 6);
				write(2, tmp->next->str, ft_strlen(tmp->next->str, 0));
				write(2, ": No such file or directory\n", 28);
				cmd->status = 1;
				cmd->stop = 1;
				close(fd);
				return ;
			}
			cmd->fd_master[1] = fd;
		}
		else if (f == 3)
			ft_heredoc(cmd, tmp->next->str, NULL, 0);
		tmp = tmp->next;
		i++;
	}
	clean_redirect_tokens(&cmd->tokens);
}

void	clean_redirect_tokens(t_token **list)
{
	t_token	*tmp;
	int		j;

	tmp = (*list);
	while (tmp)
	{
		is_separator(tmp->str, &j);
		if (j != 0)
		{
			token_remove(list, tmp->next);
			token_remove(list, tmp);
			tmp = *list;
		}
		else
			tmp = tmp->next;
	}
}

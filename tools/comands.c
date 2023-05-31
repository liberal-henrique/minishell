/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:34:24 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/31 23:43:29 by lliberal         ###   ########.fr       */
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
		tmp->execute = get_function(tmp->args[0]);
		tmp->gpath = get_gpath(g_terminal.env, tmp->args);
		if (tmp->next)
			pipe(tmp->fd);
		else
			tmp->fd[1] = 1;
		tmp = tmp->next;
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
			fd = open(tmp->next->str, O_RDONLY, 0444);
			if (fd == -1)
			{
				write(2, "bash: ", 6);
				write(2, tmp->next->str, ft_strlen(tmp->next->str, 0));
				write(2, ": No such file or directory\n", 28);
				exit (1);
			}
			cmd->fd_master[0] = fd;
		}
		else if (f == 2)
			cmd->fd_master[1] = open(tmp->next->str, \
			O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (f == 4)
			cmd->fd_master[1] = open(tmp->next->str, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (f == 3)
		{
			ft_heredoc(cmd, tmp->next->str, NULL, 0);
			//cmd->fd_master[0] = open("./.heredoc", O_RDONLY, 0444);
			//cmd->fd_master[0] = cmd->fd[0];
		}
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

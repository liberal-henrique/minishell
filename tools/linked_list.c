/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:14:40 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/19 14:57:44 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cnt_rec(t_token *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt_rec(node->next));
}

void	clean_list_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	while (token)
	{
		tmp = token->next;
		free(token);
		token = tmp;
	}
}

void	deallocate(t_cmd *curr)
{
	t_cmd	*temp;

	temp = NULL;
	while (curr)
	{
		temp = curr->next;
		clean_list_tokens(curr->tokens);
		free_2d(curr->args);
		free(curr->gpath);
		free(curr);
		curr = temp;
	}
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
}

void	*get_function(char *name)
{
	(void) name;
	if (ft_compare("echo", name))
		return (execute_echo);
	// if (ft_compare("pwd", name))
	// 	return (execute_pwd);
	/* if (ft_compare("cd", name))
		return (execute_cd); */
	// if (ft_compare(">", name))
	// 	return (execute_redirection_out);
	// if (ft_compare("env", name))
	// 	return (execute_env);
	// if (ft_compare("export", name))
	// 	return (execute_export);
	// if (ft_compare("unset", name))
	// 	return (execute_unset);
	/* if (ft_compare("<", name))
		return (execute_redirection_in);
	if (ft_compare("<<", name))
		return (execute_redirection_heredoc); */
	// if (ft_compare(">>", name))
	// 	return (execute_redirection_append_out);
	return (execute_default);
}

void	print_linked(t_cmd *curr)
{
	int	i;

	printf("+++++++++++++++++++++++++++++++++++++++\n");
	printf("%i\n", g_terminal.fquotes);
	while (curr)
	{
		printf("------------------------------------\n");
		i = -1;
		token_print(curr->tokens);
		while (curr->args[++i])
			printf("Argumento: %i, %s\n", i, curr->args[i]);
		printf("path: %s\n", curr->gpath);
		printf("fd_master[0]: %i\n", curr->fd_master[0]);
		printf("fd_master[1]: %i\n", curr->fd_master[1]);
		curr = curr->next;
	}
}

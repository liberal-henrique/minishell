/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/18 15:41:43 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

void	separator_cmd(char **new, char **s, int *i, int j)
{
	// if ((*(*s)) == '|')
	// 	*(*new)++ = (3 - *i);
	// else
	// 	*(*new)++ = 2;
	// if ((*(*s) != '|') || *i || (*(*s)++ != '|'))
	// 	*(*new)++ = *(*s)++;
	// if (j == 2)
	// 	*(*new)++ = *(*s)++;
	// *(*new)++ = 2;
	// *i = 1;

	*(*new)++ = (3 - *i);
	if ((*(*s) != '|') || *i || (*(*s)++ != '|'))
		*(*new)++ = *(*s)++;
	if (j == 2)
		*(*new)++ = *(*s)++;
	*(*new)++ = 2;
	*i = 1;
}

int	create_str(char *new, char *s, int i, char set)
{
	int	j;
	int	flag_quotes;

	flag_quotes = 0;
	while (*s)
	{
		if (!set && is_quote(*s))
			set = *s;
		else if (*s == '\"')
			flag_quotes += 1;
		else if (set == *s && *s)
			set = 0;
		else if (!set && is_space(*s))
			(*s) = '2';
		if (!set && is_separator(s, &j))
		{
			// separator_cmd(&new, &s, &i, j);
			// *new++ = ('3' - i);
			if (*s == '|')
				*new++ = '3';
			else
				*new++ = '2';
			if ((*s != '|') || i || (*s++ != '|'))
				*new++ = *s++;
			if (j == 2)
				*new++ = *s++;
			*new++ = '2';
			i = 1;
		}
		else
		{
			*new++ = *s++;
			i = 0;
		}
	}
	*new = 0;
	return (flag_quotes);
}


void	ft_phrases(const char *line)
{
	char	*new;
	char	**arr;
	int		flag;
	t_cmd	*list;

	new = malloc_ob(ft_strlen((char *)line, 0) * 2);
	if (!new)
		return ;
	flag = create_str(new, (char *)line, 0, 0);
	arr = ft_split(new, '3');
	list = create_cmds(arr);
	while (list)
	{
		token_print(list->tokens);
		printf("in: %d\n", list->fd_master[0]);
		printf("out: %d\n", list->fd_master[1]);
		list = list->next;
	}
	// g_terminal.begin = list;
	// list->flag_quotes = flag;
	// if (!list)
	// 	return ;
	free(new);
	free_2d(arr);

}

t_cmd	*create_cmds(char **arr)
{
	t_cmd	*begin;
	t_cmd	*end;
	t_cmd	*tmp;
	int		i;

	begin = NULL;
	end = NULL;
	i = -1;
	while (arr[++i])
		end = insert_end(&begin, arr[i], end);
	tmp = begin;
	while (tmp)
	{
		cmd_redirect(tmp);
		tmp = tmp->next;
	}
	return (begin);
}

void	ft_tokens(t_token **token, char *phrase)
{
	char **tokens;
	int	i;

	tokens = ft_split(phrase, '2');
	i = -1;
	while (tokens[++i])
		token_add_back(token, tokens[i]);
}

void	cmd_redirect(t_cmd *cmd)
{
	t_token	*tmp;
	int f;
	int	i;

	tmp = cmd->tokens;
	i = 0;
	while (tmp)
	{
		f = is_redirect(tmp->str);
		if (f == 1) //infile
			cmd->fd_master[0] = open(tmp->next->str, O_RDONLY, 0444);
		else if (f == 2) //outfile
			cmd->fd_master[1] = open(tmp->next->str, O_CREAT | O_TRUNC | O_RDWR, 0644);
		tmp = tmp->next;
		i++;
	}
	//token_remove(&cmd->tokens, cmd->tokens->next->next);
	//token_remove(&cmd->tokens, 1);
	clean_redirect_tokens(&cmd->tokens);
}

//< infile cat | wc > outfile

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

	/* int f;
	while (tokens_first)
	{
		f = is_redirect(tokens_first->str);
		// printf("f: %d\n", f);
		if (f == 1) //infile
		{
			fd_master[0] = open(tokens0[i + 1], O_RDONLY, 0444);
			token_remove(&tokens_first, i);
			token_remove(&tokens_first, i+1);
		}
		else if (f == 2) //outfile
		{
			fd_master[1] = open(tokens0[i + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
			token_remove(&tokens_first, i);
			token_remove(&tokens_first, i+1);
		}
		tokens_first = tokens_first->next;
	}
	while (tokens_second)
	{
		f = is_redirect(tokens_second->str);
		printf("f: %d\n", f);
		tokens_second = tokens_second->next;
	} */



	//< infile cat | wc > outfile

	// printf("%s\n", new);
	// list = create_args(new);
	// g_terminal.begin = list;
	// list->flag_quotes = flag;
	// if (!list)
	// 	return ;
	// execute_main(list, 0);
	// ft_wait(list);
	//print_linked(list);
	// deallocate(list);
	// free_2d(tokens0);
	// free_2d(tokens1);



// while (tokens0[++i])
// 	{
// 		int f;

// 		f = is_redirect(tokens0[i]);
// 		if (f == 1) //infile
// 			master_fd[0] = open(tokens0[i + 1], O_RDONLY, 0444);
// 		else if (f == 2) //outfile
// 			master_fd[1] = open(tokens0[i + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);

// 	}
// 	i = -1;
// 	while (tokens1[++i])
// 	{
// 		int f;

// 		f = is_redirect(tokens0[i]);
// 		if (f == 1) //infile
// 		{
// 			master_fd[0] = open(tokens0[i + 1], O_RDONLY, 0444);
// 			token_remove(i);
// 			token_remove(i+1);
// 		}
// 		else if (f == 2) //outfile
// 		{
// 			master_fd[1] = open(tokens0[i + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
// 			token_remove(i);
// 			token_remove(i+1);
// 		}

// 	}

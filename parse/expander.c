/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:31:20 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/31 23:36:17 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
	|| (c >= '0' && c <= '9') || (c == '_'));
}
// echo $?hello
// echo he$?llo

char	*find_needle(char *stack, char *needle)
{
	int	i;
	int	k;
	char *new;
	char *itoa;

	i = -1;
	if (!stack || !needle)
		return (stack);
	while (stack[++i])
	{
		//printf("char: %c\n", stack[i]);
		k = 0;
		while (stack[i + k] == needle[k] && needle[k] != '\0')
			k++;
		if (k == (int)ft_strlen(needle, 0))
		{
			new = ft_strdup(stack);
			free(stack);
			itoa = ft_itoa(g_terminal.status);
			stack = ft_replace(new, needle, itoa);
			free(itoa);
			free(new);
		}
	}
	return (stack);
}

char	*expander(char *str)
{
	char	name[1024];
	int		index;
	int		start;
	int		end;
	char	*new;

	// printf("%s\n", str);
	start = -1;
	end = 0;
	index = 0;
	str = find_needle(str, "$?");
	while (str[index] && end == 0)
	{
		if (start == -1 && str[index] == '$')
			start = index;
		else if (start >= 0 && !check(str[index]) && ++end)
			name[index] = 0;
		if (end == 0 && start != -1)
			name[index - start] = str[index];
		index++;
	}
	if (start == -1)
		return (str);
	new = ft_replace(str, name, find_var(&name[1]));
	free(str);
	return (expander(new));
}

/* char	*remove_quotes(char *str)
{
	char	*new;
	int		len;

	len = 0;
	new = malloc_ob(ft_strlen(str, 0));
	printf("%s\n", str);
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str++;
		else
			new[len++] = *str++;
	}

	free(str);
	return (new);
} */

char	*remove_quotes_2(char *str, int fsingle, int fdouble)
{
	char	*new;
	int		end;
	int		i;
	int		j;

	end = 0;
	new = malloc_ob(ft_strlen(str, 0) + 1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && fsingle == 2)
			;
		else if (str[i] == '\"' && fdouble == 2)
			;
		else
		{
			new[j] = str[i];
			j++;
		}
	}
	return (new);
}
// echo ola''''"asdf" -- > olaasdf | ola"asdf"
char	*remove_quotes(char *str)
{
	int		fsingle;
	int		fdouble;
	char	*new;
	int		i;

	fsingle = 0;
	fdouble = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && fsingle == 0 && (fdouble == 0 || fdouble == 2))
			fsingle = 1;
		else if (str[i] == '\'' && fsingle == 1)
			fsingle = 2;
		else if (str[i] == '\"' && (fsingle == 0 || fsingle == 2) && fdouble == 0)
			fdouble = 1;
		else if (str[i] == '\"' && fdouble == 1)
			fdouble = 2;
	}
	new = remove_quotes_2(str, fsingle, fdouble);
	free(str);
	return (new);
}

void	expander_args(t_cmd *list)
{
	t_token	*temp;
	char	*tmp_str;
	char	*s;

	while (list)
	{
		temp = list->tokens;
		while (temp)
		{
			if (!ft_strcmp(temp->str, "$?"))
			{
				free(temp->str);
				temp->str = ft_itoa(g_terminal.status);
				return ;
			}
			s = temp->str;
			if (!ft_strcmp(temp->str, "$") || !ft_strcmp(temp->str, "\"$\""))
				temp->str = remove_quotes(temp->str);
			else if (s && !(*s == '\'' && s[ft_strlen(s, 0) - 1] == '\''))
			{
				tmp_str = expander(s);
				temp->str = remove_quotes(tmp_str);
			}
			else if (s && (*s == '\'' && s[ft_strlen(s, 0) - 1] == '\''))
					temp->str = remove_quotes(s);
			temp = temp->next;
		}
		list = list->next;
	}
}

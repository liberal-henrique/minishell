/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:14:40 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 11:19:29 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

void	put_str(char *s)
{
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

int	check_group(char c)
{
	return (c == '(' || c == ')' || c == '!' || c == '%' \
	|| c == '^' || c == '@' || c == '#' || c == '~' || c == '>' \
	|| c == '>' || c == '<' || c == ':' || c == '*' || c == '\\' \
	|| c == '&');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:13:23 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/06 12:52:28 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substring(const char *str, int start, int end)
{
	char	*new;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	new = malloc_ob((end - start) + 1);
	if (!new)
		return (NULL);
	while (start <= end && str)
		new[i++] = str[start++];
	return (new);
}

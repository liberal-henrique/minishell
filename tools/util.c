/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:05:45 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 10:29:52 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *a, char set)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a && a[i] && a[i] != set)
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	char	*tmp;
	int		i_dest;
	int		i_src;

	i_dest = 0;
	i_src = -1;
	tmp = dest;
	while (*dest)
		dest++;
	while (src[++i_src])
		dest[i_dest + i_src] = src[i_src];
	dest[i_dest + i_src] = '\0';
	return (tmp);
}

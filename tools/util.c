/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:05:45 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/17 16:36:58 by lliberal         ###   ########.fr       */
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
	while (a[i])
	{
		if (a[i] == set)
			break ;
		i++;
	}
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	length;
	char	*dest;

	if (!s1 || !s2)
		return (0);
	length = (ft_strlen(s1, 0) + ft_strlen(s2, 0));
	dest = malloc(length + 1);
	if (!dest)
		return (0);
	ft_strcpy(dest, (char *)s1);
	ft_strcat(dest, (char *)s2);
	return (dest);
}

char	*ft_strdup(const char	*s1)
{
	char			*str1;
	char			*dup;
	size_t			size_s1;
	unsigned int	i;

	if (!s1)
		return (NULL);
	str1 = (char *)s1;
	i = -1;
	size_s1 = ft_strlen(str1, 0) + 1;
	dup = malloc_ob(size_s1);
	if (!dup)
		return (NULL);
	while (str1[++i])
		dup[i] = s1[i];
	return (dup);
}

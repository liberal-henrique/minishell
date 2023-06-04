/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:05:45 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/04 15:16:48 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned int	nb_size(long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	ln;

	ln = n;
	len = nb_size(ln);
	str = malloc_ob((len + 1));
	if (!str)
		return (NULL);
	if (ln == 0)
		str[0] = '0';
	if (ln < 0)
	{
		str[0] = '-';
		ln *= -1;
	}
	len--;
	while (ln != 0)
	{
		str[len] = ln % 10 + 48;
		ln /= 10;
		len--;
	}
	return (str);
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

void	*free_ob(void *p, void *resul)
{
	free(p);
	return (resul);
}

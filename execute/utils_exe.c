/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:57:00 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/24 17:00:50 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**clone_env(char **env)
{
	char	**clone;
	int		i;
	int		i_c;

	i = 0;
	i_c = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	clone = malloc_ob(sizeof(char *) * (i + 1));
	if (!clone)
		return (NULL);
	i = -1;
	while (env[++i])
		clone[i_c++] = ft_strdup(env[i]);
	return (clone);
}

char	**increase_env(char **env)
{
	char	**clone;
	int		i;
	int		i_c;

	i = 0;
	i_c = 0;
	while (env[i])
		i++;
	i += 1;
	clone = malloc_ob(sizeof(char *) * (i + 1));
	if (!clone)
		return (NULL);
	i = -1;
	while (env[++i])
		clone[i_c++] = ft_strdup(env[i]);
	return (clone);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*str_join(char *old, char *seg, char c)
{
	int		old_len;
	int		seg_len;
	int		i;
	int		j;
	char	*new;

	old_len = ft_strlen(old, 0);
	seg_len = ft_strlen(seg, 0);
	new = (char *)malloc(old_len + seg_len + 2);
	i = -1;
	while (++i < old_len)
		new[i] = old[i];
	new[i++] = c;
	j = -1;
	while (++j < seg_len)
		new[i++] = seg[j];
	new[i] = 0;
	/* if (old)
		free(old); */
	return (new);
}

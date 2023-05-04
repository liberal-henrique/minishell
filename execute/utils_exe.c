/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:57:00 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/04 14:57:12 by lliberal         ###   ########.fr       */
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

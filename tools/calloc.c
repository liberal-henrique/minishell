/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:44:44 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/04 13:46:57 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*malloc_ob(size_t length)
{
	void				*tmp;
	unsigned char		*element;

	if (length < 1)
		return (NULL);
	tmp = malloc(length);
	if (!tmp)
		return (NULL);
	element = (unsigned char *)tmp;
	while (length-- > 0)
		*element++ = 0;
	return (tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:31:20 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/24 23:50:28 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_len_value(char **env, char *str)
{
	size_t	length_received;
	int	len_var;
	int	len;
	int	i;

	i = -1;
	len = 0;
	len_var = 0;
	length_received = ft_strlen(str, 0);
	while (env[++i])
	{
		len_var = ft_strlen(env[i], '=');
		if (ft_strncmp(env[i], str, len_var) == 0 && env[i][len_var] == '=')
			len = ft_strlen(env[i], 0) - (ft_strlen(env[i], '='));
	}
	return (len);
}

void	put_five(char **env, char *str)
{
	int		j;

	j = 0;
	(void) env;
	while (*str)
	{
		if (j == 0 && *str == '\"')
			j = 1;
		else if (j == 1 && *str == '\"')
			j = 0;
		if (j == 1 && *str == '$')
			*str++ = 5;
		else
			str++;
	}
}

char	*return_value(char **env, char *str)
{
	char	*value;
	int		i;
	int		len;
	int		len_var;

	i = -1;
	len = 0;
	len_var = 0;
	value = malloc_ob(2048);
	while (env[++i])
	{
		len_var = ft_strlen(env[i], '=');
		if (ft_strncmp(env[i], str, len_var) == 0 && env[i][len_var] == '=')
		{
			value = ft_strdup(ft_substring(env[i], (ft_strlen(env[i], '=') + 1), ft_strlen(env[i], 0)));
		}
	}
	return (value);
}

char	*ft_strjoin_expansion(char *line, char *buf)
{
	char	*new_line;
	int		i;
	int		k;
	int		buf_len;
	int		line_len;

	buf_len = ft_strlen(buf, 0);
	line_len = ft_strlen(line, 0);
	new_line = (char *)malloc(buf_len + line_len + 200);
	if (!new_line)
		return (NULL);
	i = -1;
	k = -1;
	while (++i < line_len)
		new_line[i] = line[i];
	while (++k < buf_len)
		new_line[i++] = buf[k];
	new_line[i] = 0;
	free(line);
	return (new_line);
}

char	*ft_strjoin_char(char *line, char c)
{
	char	*new_line;
	int		i;
	int		k;
	int		buf_len;
	int		line_len;

	buf_len = 1;
	line_len = ft_strlen(line, 0);
	new_line = (char *)malloc(buf_len + line_len + 200);
	if (!new_line)
		return (NULL);
	i = -1;
	k = -1;
	while (++i < line_len)
		new_line[i] = line[i];
	while (++k < buf_len)
		new_line[i++] = c;
	new_line[i] = 0;
	free(line);
	return (new_line);
}

char	*putraska(char *str)
{
	int	i;
	int	f;
	int	g;
	int	k;
	char *new;

	new = malloc_ob(2048);
	i = 0;
	g = 0;
	f = 0;
	k = 0;
	while (*str)
	{
		if (f == 0 && *str == '\'')
			f = 1;
		else if (f == 1 && *str == '\'')
			f = 0;
		if (f == 0 && g == 0 && *str == '\"')
			g = 1;
		else if (f == 0 && g == 1 && *str == '\"')
			g = 0;
		if (f == 0 && g == 0 && k == 0 && *str == '$')
		{
			new[i++] = '"';
			new[i++] = '$';
			k = 1;
		}
		else if (f == 0 && g == 0 && k == 1 && (is_space(*str) || *str == 0))
		{
			new[i++] = '"';
			new[i++] = ' ';
			k = 0;
		}
		else
			new[i++] = *str;
		str++;
	}
	if (k == 1)
		new[i] = '"';
	return (new);
}

char	*expander2(char **env, char *str)
{
	char	*tmp;
	char	*put;
	char	*new;
	int		i;
	int		j;
	int		length;

	i = -1;
	j = 0;
	length = 0;
	tmp = malloc_ob(1024);
	put = putraska(str);
	put_five(env, put);
	new = malloc_ob((ft_strlen(str, 0) * 200));
	while (env && put[++i])
	{
		if (put[i] == 5 && i++)
		{
			while (!is_space(put[i]) && put[i] && put[i] != '\"')
				tmp[length++] = put[i++];
			tmp[length] = 0;
			new = ft_strjoin_expansion(new, return_value(env, tmp));
			j += ft_strlen(new, 0);
			length = 0;
			i--;
		}
		else
			if (put[i] != '\"')
				new = ft_strjoin_char(new, put[i]);
	}
	return (new);
}

#include <stdio.h>
#include <stdlib.h>
// // echo "ola, $HOME" > outfile - $HOME

// size_t	ft_strlen(const char *a, char set)
// {
// 	int	i;

// 	i = 0;
// 	while (a && a[i] && a[i] != set)
// 		i++;
// 	return (i);
// }

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
	{
		*element = 0;
		element++;
	}
	return (tmp);
}

size_t	ft_strlen(const char *a, char set)
{
	int	i;

	i = 0;
	while (a && a[i] && a[i] != set)
		i++;
	return (i);
}

int	check_contain(char *origin, char *set)
{
	int	position;
	int	i;
	int	j;

	i = -1;
	position = 0;
	while (set && origin[++i])
	{
		j = 0;
		while (origin[i] && origin[i] == set[j])
		{
			if (j == 0)
				position = i;
			i++;
			j++;
		}
		if (!set[j])
			return (position);
	}
	return (-1);
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

char	*ft_replace(char *dst, char *to, char *rep)
{
	char	*new;
	int		start;
	int		i;
	int		j;

	start = check_contain(dst, to);
	if (start < 0 || !to || !rep)
		return (ft_strdup(dst));
	new = malloc_ob((ft_strlen(dst, 0) - \
	(ft_strlen(to, 0)) + ft_strlen(rep, 0) + 1));
	j = -1;
	i = 0;
	while (dst[++j])
	{
		if (j == start)
			while (*rep)
				new[i++] = *rep++;
		if (j == start)
			j += (ft_strlen(to, 0) - 1);
		else
			new[i++] = dst[j];
	}
	return (new);
}

// //  check_contain("echo ola, $HOME > outfile", "$HOME")

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
	while (start < end && str)
		new[i++] = str[start++];
	return (new);
}


// char	*check_delimiter(char *delimiter, char set, int start, int i)
// {
// 	char	*new;
// 	int		end;

// 	end = 0;
// 	if (!delimiter)
// 		return (ft_strdup(delimiter));
// 	while (delimiter[++i])
// 	{
// 		if (set == 0 && (delimiter[i] == '\'' || delimiter[i] == '\"'))
// 		{
// 			start = i + 1;
// 			set = 1;
// 		}
// 		else if (set == 1 && (delimiter[i] == '\'' || delimiter[i] == '\"'))
// 			end = i;
// 	}
// 	new = ft_substring(delimiter, start, end);
// 	return (new);
// }


int main(void)
{
	// printf("Estou aqui: %s\n", check_delimiter("", 0, 0, -1));
	printf("Estou aqui: %s\n", ft_replace("Luiz Henrique\"$HOME\" LIberal de Souza", "\"$HOME\"", "$PATH"));
}

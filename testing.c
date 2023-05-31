#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void	*malloc_ob(size_t length);

size_t	ft_strlen(const char *a, char set)
{
	int	i;

	i = 0;
	while (a && a[i] && a[i] != set)
		i++;
	return (i);
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



// echo $?HELLO --> echo 0HELLO


char	*find_needle(char *stack, char *needle)
{
	int	i;
	int	k;
	char *new;

	i = -1;
	if (!stack || !needle)
		return (stack);
	while (stack[++i])
	{
		//printf("char: %c\n", stack[i]);
		k = 0;
		while (stack[i + k] == needle[k] && needle[k] != '\0')
			k++;
		if (k == ft_strlen(needle, 0))
		{
			new = ft_strdup(stack);
			free(stack);
			stack = ft_replace(new, needle, "0");
			free(new);
		}
	}
	return (stack);
}

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

long int ft_atoi(const char *str, long int res, int i, int sign)
{
	if (!str)
		return (0);
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
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

// int	main(void)
// {
// 	char *input;

// 	input = "223372036854775808LL";

// 	if (ft_strcmp())
// 		printf("Number is too large!\n");
// 	else
// 		printf("Number is within the valid range.\n");
// 	return 0;
// }

int	ft_isnum_t(char c)
{
	return (c >= '0' && c <= '9');
}

int	main(void)
{
	printf("%i\n", ft_isnum_t('1'));
}

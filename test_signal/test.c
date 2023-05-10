#include<signal.h>
#include<stdarg.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include<readline/readline.h>
#include<readline/history.h>

// void	sighandler()
// {
// 	printf("\n");
// 	rl_on_new_line(); // Regenerate the prompt on a newline
//     rl_replace_line("", 1); // Clear the previous text
//     rl_redisplay();
// }

// int	main(int ac, char **av)
// {
// 	char	*line;

// 	signal(SIGINT, sighandler);
// 	signal(SIGQUIT, SIG_IGN);
// 	while (1)
// 	{
// 		line = readline("Minishell$ ");
// 		add_history(line);
// 		if (!line)
// 			exit(0);
// 		free(line);
// 	}
// 	return (0);
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
		*element++ = 0;
	return (tmp);
}

int	ft_strlen(const char *a, char set)
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


int	check_contain(char *origin, char *set)
{
	int	i;
	int	j;
	int	position;

	i = -1;
	position = 0;
	while (origin[++i])
	{
		j = 0;
		while (origin[i] == set[j] && origin[i])
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
	if (start < 0)
		return (NULL);
	new = malloc_ob(((ft_strlen(dst, 0) - \
	ft_strlen(to, 0)) + ft_strlen(rep, 0) + 1));
	if (!new)
		return (NULL);
	j = -1;
	i = 0;
	while (dst[++j])
	{
		if (i == start)
			j += (ft_strlen(to, 0) - 1);
		if (i == start)
			while (*rep)
				new[i++] = *rep++;
		else
			new[i++] = dst[j];
	}
	// free(dst);
	return (new);
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

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	unsigned int	count;
// 	const char		*str;
// 	char			*dest;

// 	count = 0;
// 	str = s;
// 	if (!s)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (len <= ft_strlen(s))
// 		dest = malloc_ob((len + 1));
// 	else
// 		dest = malloc_ob((ft_strlen(s) - start + 1));
// 	if (!dest)
// 		return (NULL);
// 	while (str[start] && count < len)
// 	{
// 		dest[count] = str[start + count];
// 		count++;
// 	}
// 	return (dest);
// }

int main(void)
{
	// char *name;

	// name = ft_substr("Luiz Henrique", );

	int i = ft_strlen("name=luiz", '=') + 2;

	printf("%i\n", i);
	// name = ft_replace("luiz Henrique", "luiz Henrique", "ola1");
	printf("%i\n", ft_strncmp("name=luiz", "name=la1", i));
	// printf("%s\n", name);
	// free(name);
}

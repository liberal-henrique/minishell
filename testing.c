#include <stdio.h>

size_t	ft_strlen(const char *a, char set)
{
	int	i;

	i = 0;
	while (a && a[i] && a[i] != set)
		i++;
	return (i);
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

int	main(void)
{
	char *var = "banana=";
	char *arg = "bana";

	if (ft_strncmp(var, arg, ft_strlen(var, '=')) == 0 && ft_strlen(arg, 0) == ft_strlen(var, '='))
		printf("sim\n");
	else
		printf("nao\n");

	return (0);
}

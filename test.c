// int	main(void)
// {
// 	char	strings[10][100] = {
// 		"0hello=primeiro",
// 		"9Ola=oinono",
// 		"8Salut=oioitavo",
// 		"7Hallo=oisetimo",
// 		"6Ciao=oisexto",
// 		"5Hola=oiquinto",
// 		"4Oi=oiquarto",
// 		"3Danke=Obrigadoterceiro",
// 		"2Thanks=Obrigadosegundo",
// 		"1Merci=Obrigadoomelhor",
// 	};

// 	int		i = -1;
// 	t_expo	*begin = NULL;
// 	t_expo	*end = NULL;
// 	while(++i < 10)
// 		end = insert_end(&begin, strings[i], &end);
// 	bubblesort(begin);
// 	print_list(begin);
// }

// int	env_variable_replaced(char *cmd, int flag)
// {
// 	int		length;
// 	size_t	len_name;
// 	int		len_variable;

// 	length = -1;
// 	len_name = ft_strlen(cmd, '=');
// 	len_variable = 0;
// 	while (g_terminal.expo[++length] && cmd)
// 	{
// 		if (ft_strlen(g_terminal.expo[length], '=') > len_name)
// 			len_variable = ft_strlen(g_terminal.expo[length], '=');
// 		else
// 			len_variable = len_name;
// 		if (ft_strncmp(g_terminal.expo[length], cmd, len_variable) == 0)
// 		{
// 			g_terminal.expo[length] = ft_replace(g_terminal.expo[length], g_terminal.expo[length], cmd);
// 			flag += 1;
// 		}
// 	}
// 	return (flag);
// }

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;

	t_expo	*begin;
	t_expo	*end;
	int		counter = 0;
	int i = -1;
	begin = NULL;
	end = NULL;
	while (env[++i])
	{
		end = insert_end(&begin, env[i], &end);
		counter++;
	}
	bubblesort(begin);
	print_list(begin);
}

char	**create_expo(char **env)
{
	char	**expo;
	int		i;
	int		length;
	int		j;
	int		j_min;

	j = 0;
	i = 0;
	expo = clone_env(env);
	length = ft_strlen_2d(env);
	while (i < (length - 1))
	{
		j_min = i;
		while (j < (length - 1))
		{
			if (ft_strcmp(expo[j], expo[j_min]) < 0)
				j_min = j;
			j++;
		}
 		i++;
	}
	return (expo);
}


	// while (list)
	// {
	// 	token_print(list->tokens);
	// 	// printf("in: %d\n", list->fd_master[0]);
	// 	// printf("out: %d\n", list->fd_master[1]);
	// 	list = list->next;
	// }


// t_cmd	*insert_end(t_cmd **root, char *s, t_cmd *end)
// {
// 	t_cmd	*new_node;

// 	new_node = malloc_ob(sizeof(t_cmd));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->next = NULL;
// 	new_node->args = ft_split(s, 2);
// 	new_node->execute = get_function(new_node->args[0]);
// 	new_node->gpath = get_gpath(g_terminal.env, new_node->args);
// 	pipe(new_node->fd);
// 	if (!(*root))
// 		*root = new_node;
// 	else
// 		end->next = new_node;
// 	return (new_node);
// }

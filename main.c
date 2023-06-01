/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:55:52 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/02 00:14:25 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_terminal	g_terminal;

void	sighandler()
{
	if (g_terminal.heredoc == 1)
	{
		g_terminal.stopheredoc = 1;
		g_terminal.status = 130;
		g_terminal.heredoc = 0;
		write(1, "\n", 1);
		exit (130);
	}
	if (g_terminal.in_cmd == 1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_terminal.status = 130;
		return ;
	}
	else
	{
		g_terminal.status = 130;
		//g_terminal.in_cmd = 1;
		return ;
	}
}

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
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (ln == 0)
		str[0] = '0';
	if (ln < 0)
	{
		str[0] = '-';
		ln *= -1;
	}
	str[len] = '\0';
	len--;
	while (ln != 0)
	{
		str[len] = ln % 10 + 48;
		ln /= 10;
		len--;
	}
	return (str);
}

char	**invent_env()
{
	//t_expo	*expo;
	char	**env;
	char	*cwd;

	env = (char **)malloc_ob(sizeof(char *) * 4);
	cwd = getcwd(NULL, 0);
	env[0] = str_join("PWD", cwd, '=');
	env[1] = str_join("SHLVL", ft_itoa(g_terminal.SHLVL), '=');
	env[2] = str_join("_", "/usr/bin/env", '=');
	free(cwd);
	return (env);
}

t_expo	*invent_expo(char **env)
{
	t_expo	*begin;
	t_expo	*end;
	int		i;

	begin = NULL;
	end = NULL;
	i = -1;
	while (env[++i])
		end = insert_end_expo_list(&begin, env[i], &end);
	bubblesort(begin);
	return (begin);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) ac;
	(void) av;
	g_terminal.heredoc = 0;
	g_terminal.stopheredoc = 0;
	g_terminal.in_cmd = 1;
	if (ft_strlen_2d(env) != 0)
	{
		g_terminal.env = clone_env(env);
		g_terminal.expo = create_expo(env);
	}
	else
	{
		g_terminal.env = invent_env();
		g_terminal.expo = invent_expo(g_terminal.env);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	while (1)
	{
		g_terminal.in_cmd = 1;
		g_terminal.childs = 0;
		line = readline("Minishell$ ");
		if (!line)
		{
			cleanall(g_terminal.begin, 1);
			printf("exit\n");
			exit(STATUS_SUCCESS);
		}
		if (line && line[0] != 0)
		{
			add_history(line);
			ft_phrases(line);
			free(line);
			cleanall(g_terminal.begin, 0);
		}
	}
	return (0);
}

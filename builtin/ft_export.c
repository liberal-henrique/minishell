/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:01:23 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/10 18:58:24 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


size_t	ft_strlen_2d(char **a)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
		i++;
	return (i);
}

//    se o argumento do export existir no env teremos de alterar o valor com o
// valor poisterior ao '='; (O Vasco apontou que ha um erro no ft_strncmp, pois
// elecompara o manor ate o =)

//    se o argumento do export nao existir no env teremos de criar um novo topico
// dentro de env.

//    se o export nao tiver nenhum argumento precisaremos retornar o env em ordem
// alfabetica e com o declare -x antes das variaveis.
	// Contudo, para evitar de termos de fazer MULTIPLAS alteracoes no env para
	// quando formos retornar o export. O Vasco sugeriu que criassemos um segundo
	// array bidimensional dentro da nossa variavel global. Assim poderiamos armazenar
	// o retorno do nosso export com suas peculiaridades e dentro do nosso env as coisas
	// como recebemos. Teremos de tomar atencao para caso tenhamos de alterar algo, pois
	// assim teremos de alterar em dois lugares.

// Export sem argumentos apenas imprimi toda a env em ordem alfabetica e
//com o declare x- na frente.
// Export com argumento apenas atualiza a variavel de ambiente respectiva
//ou a cria caso nao exista. Mas nao imprimi o resultado.

int	env_variable_replaced(char *cmd, int flag)
{
	int		length;
	size_t	len_name;
	int		len_variable;

	length = -1;
	len_name = ft_strlen(cmd, '=');
	len_variable = 0;
	while (g_terminal.env[++length] && cmd)
	{
		if (ft_strlen(g_terminal.env[length], '=') > len_name)
			len_variable = ft_strlen(g_terminal.env[length], '=');
		else
			len_variable = len_name;
		if (ft_strncmp(g_terminal.env[length], cmd, len_variable) == 0)
		{
			g_terminal.env[length] = ft_replace(g_terminal.env[length], g_terminal.env[length], cmd);
			flag += 1;
		}
	}
	return (flag);
}

// Eu nao estou a fazer a limpeza da conteudo anterior
//da variavel global pois recebi uma mensagem de
//double free()
void	create_variable(char *cmd)
{
	char	**new_env;
	int		i;

	new_env = increase_env(g_terminal.env);
	i = -1;
	while (new_env[++i])
		new_env[i] = g_terminal.env[i];
	new_env[i] = ft_strdup(cmd);
	// free_2d(g_terminal.env);
	g_terminal.env = new_env;
}

void	print_2d(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

int	execute_export(t_cmd *cmd)
{
	int	flag;

	// No futuro vamos imprimir aqui o g_terminal.expo
	if (!cmd->args[1])
		print_2d(g_terminal.env);
	flag = env_variable_replaced(cmd->args[1], 0);
	if (flag == 0)
		create_variable(cmd->args[1]);
	return (STATUS_SUCCESS);
}

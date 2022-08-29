/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:00:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/08/29 11:44:56 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//Modifications from francis branch

char	*get_cmd(char *input)
{
	int		i;
	int		j;
	char	*cmd;

	i = 2;
	j = 0;
	cmd = calloc(sizeof(char), ft_strlen(input) - 2);
	while (input[++i])
	{
		cmd[j] = input[i];
		j++;
	}
	return (cmd);
}

int	init_struct(t_vars *vars)
{
	vars->prompt = "\e[1;34mminishell >> \e[0;37m";
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	char	*input;
	//char	**args;
	t_vars	vars;

	i = -1;
	printf("%s\n", argv[0]);
	printf("%s\n", argv[1]);
	if (argc != 1 || !argv[0])
	{
		printf("Error: Execute as ./minishell\n");
		return (1);
	}
	if (init_struct(&vars))
		return (1);
	printf("%s", CLEAN);
	input = readline(vars.prompt);
	while (input)
	{
		//args = lexer(input);
		/*	Faire le lexer qui va séparer les arguments reçus en input
			Les mettre dans un double array
			Envoyer les args dans leur fonction respective (Adapter les fonctions déjà faites */
		if (!ft_strncmp(input, "Exit", 4) || !ft_strncmp(input, "exit", 4))
			return (0);
		if (!ft_strncmp(input, "env", 3))
			print_env();
		if (!ft_strncmp(input, "pwd", 3))
			print_path();
		if (!ft_strncmp(input, "echo ", 5))
			echo(input);
		if (!ft_strncmp(input, "cd", 2))
			cd(input);
		if (execute_input(&vars, input))
			return (0);
		input = readline(vars.prompt);
	}
	return (0);
}

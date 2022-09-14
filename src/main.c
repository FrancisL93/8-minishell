/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:00:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/14 11:32:35 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Le main doit voir le dernier exit status

int	init_struct(t_vars *vars, char **envp)
{
	int	i;

	i = 0;
	vars->var = malloc(sizeof(*vars->var));
	vars->pipe = 1;
	while (envp[i])
		i++;
	vars->env = malloc(sizeof(char **) * (i + 1));
	i = -1;
	while (envp[++i])
		vars->env[i] = ft_strdup(envp[i]);
	vars->env[i] = NULL;
	set_prompt(vars);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_vars	vars;

	if (argc == 1 && argv[0])
	{
		if (init_struct(&vars, envp))
			return (1);
		printf("%s", CLEAN);
		input = readline(vars.prompt);
		while (input)
		{
			if (!ft_strncmp("exit", tolower_str(input, 0), 4))
				quit_terminal(&vars, vars.var);
			if (input && *input)
				add_history(input);
			lexer(input, &vars);
			if (vars.token.tokens[0])
				execute(&vars);
			clean_command(&vars, input);
			set_prompt(&vars);
			input = readline(vars.prompt);
		}	
	}
	else
		printf("Error: Execute as ./minishell\n");
	return (1);
}

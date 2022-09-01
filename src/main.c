/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:00:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/01 15:49:08 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//Modifications from francis branch

int	init_struct(t_vars *vars)
{
	set_prompt(vars);
	vars->var = malloc(sizeof(*vars->var));
	vars->built_in = 0;
	vars->pipe = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	char	*input;
	t_vars	vars;

	if (argc == 1 && argv[0])
	{
		if (init_struct(&vars))
			return (1);
		printf("%s", CLEAN);
		input = readline(vars.prompt);
		while (input)
		{
			if (input && *input)
				add_history(input);
			lexer(input, &vars);
			filter_tokens(&vars);
			if (execute(&vars, input))
				exit(1);
			set_prompt(&vars);
			free(input);
			vars.built_in = 0;
			input = readline(vars.prompt);
		}	
	}
	else
		printf("Error: Execute as ./minishell\n");
	return (1);
}

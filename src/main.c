/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:00:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/22 10:03:26 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_struct(t_vars *vars, char **envp)
{
	int		i;
	int		ii;
	int		lev;
	char	*lvl;
	char	*shlvl;

	i = 0;
	//vars->var = malloc(sizeof(*vars->var));
	vars->var = NULL;
	vars->pipe = 1;
	while (envp[i])
		i++;
	vars->env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	ii = 0;
	while (envp[++i])
	{
		if (!ft_strncmp("OLDPWD", envp[i], 6))
			i++;
		vars->env[ii] = ft_strdup(envp[i]);
		ii++;
	}
	vars->env[i] = NULL;
	lev = ft_atoi(get_variable(vars, "SHLVL"));
	lvl = ft_itoa(lev += 1);
	shlvl = ft_strjoin("SHLVL=", lvl);
	export(vars, shlvl);
	free(shlvl);
	free(lvl);
	set_prompt(vars);
	init_signals(0);
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
		printf("\nWelcome to our minishell! v938.05.42\n\n");
		input = readline(vars.prompt);
		while (input)
		{
			if (!ft_strncmp("exit", input, 4))
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
		quit_terminal(&vars, vars.var);
	}
	else
		printf("Error: Execute as ./minishell\n");
	return (1);
}

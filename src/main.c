/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:00:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/04 13:48:21 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Redirections (S'assrure avec le here doc
// que le resultat soit envoyé dans la fonction apres)
// Free
// Norme

void	set_prompt(t_vars *vars)
{
	int		i;
	char	*prompt;
	char	*tmp;

	prompt = ft_getenv(vars);
	i = ft_strlen(prompt) - 1;
	while (prompt[i] != '/')
		i--;
	tmp = ft_strjoin(GREEN, &prompt[i]);
	vars->prompt = ft_strjoin(tmp, " >> \e[0;37m");
	free(tmp);
}

void	set_shell_lvl(t_vars *vars)
{
	int		lev;
	char	*lvl;
	char	*shlvl;

	lev = ft_atoi(get_variable(vars, "SHLVL"));
	lvl = ft_itoa(lev + 1);
	shlvl = ft_strjoin("SHLVL=", lvl);
	export(vars, shlvl);
	free(shlvl);
	free(lvl);
}

int	init_struct(t_vars *vars, char **envp)
{
	int		i;
	char	*exit_stat;

	i = 0;
	vars->pipe = 1;
	vars->exit_stat = 0;
	if (set_env(vars, envp))
		return (1);
	vars->var = NULL;
	exit_stat = ft_itoa(vars->exit_stat);
	if (add_variable(vars, ft_strjoin("?=", exit_stat)))
	{
		free(exit_stat);
		return (1);
	}
	free(exit_stat);
	set_shell_lvl(vars);
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
			if (!lexer(input, &vars))
				execute(&vars);
			clean_command(&vars, input);
			set_prompt(&vars);
			input = readline(vars.prompt);
		}
		printf("%sexit\n", vars.prompt);
		quit_terminal(&vars, input);
	}
	else
		printf("Error: Execute as ./minishell\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:00:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/14 14:20:56 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//set prompt for readline depending on current directory
void	set_prompt(t_vars *vars)
{
	int		i;
	char	*prompt;

	prompt = ft_getenv(vars);
	i = ft_strlen(prompt) - 1;
	while (prompt[i] != '/')
		i--;
	vars->prompt = ft_strjoin(&prompt[i], "$ ");
}

//Set shell level in env
void	set_shell_lvl(t_vars *vars)
{
	int		lev;
	char	*lvl;
	char	*shlvl;

	lev = ft_atoi(get_variable(vars, "SHLVL"));
	lvl = ft_itoa(lev + 1);
	shlvl = ft_strjoin("SHLVL=", lvl);
	export(vars, ft_strdup(shlvl));
	free(shlvl);
	free(lvl);
}

//Initialize all variables of struct
int	init_struct(t_vars *vars, char **envp)
{
	int		i;
	char	*exit_stat;

	i = 0;
	vars->pipe = 1;
	vars->exit_stat = 0;
	vars->args = NULL;
	vars->cmds = NULL;
	vars->token.tokens = NULL;
	vars->exit_char = NULL;
	vars->fd = NULL;
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
	t_vars	vars;

	if (argc == 1 && argv[0])
	{
		if (init_struct(&vars, envp))
			return (1);
		printf("\n%sWelcome to our minishell! v938.05.42\e[0;37m\n\n", BLUE);
		vars.input = readline(vars.prompt);
		while (vars.input)
		{
			if (!lexer(&vars))
				execute(&vars);
			clean_command(&vars);
			set_prompt(&vars);
			vars.input = readline(vars.prompt);
		}
		printf("exit\n");
		quit_terminal(&vars, 0);
	}
	else
		printf("Error: Execute as ./minishell\n");
	return (1);
}

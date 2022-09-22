/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:25:38 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/22 11:46:05 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Revoir les trucs à free
void	quit_terminal(t_vars *vars, t_list *variables)
{
	int	i;

	i = -1;
	clear_history();
	while (vars->env[++i])
		free(vars->env[i]);
	free(vars->env);
	free(variables);
	free(vars->prompt);
	exit(0);
}

void	clean_command(t_vars *vars, char *input)
{
	(void)vars;
	(void)input;
/* 	int	i;
	int	j;

	j = -1;
	i = -1;
	while (vars->token.tokens && vars->token.tokens[++i])
		free(vars->token.tokens[i]);
	free(vars->token.tokens);
	i = -1;
	while (vars->cmds->cmds[++i])
		free(vars->cmds->cmds[i]);
	free(vars->cmds);
	i = -1;
	vars->pipe = 1;
	if (input && *input)
		free(input);
	free(vars->prompt); */
}

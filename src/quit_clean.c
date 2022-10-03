/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:25:38 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/01 15:46:13 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_cmds(t_vars *vars)
{
	if (vars->cmds->cmds)
		free(vars->cmds);
}

void	clean_args(t_vars *vars)
{
	// if (vars->args)
	// 	free(vars->args);
	(void) vars;
	return ;
}

void	clean_tokens(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->token.tokens)
	{
		while (vars->token.tokens[i])
			free(vars->token.tokens[i++]);
		free(vars->token.tokens);
	}
}

void	clean_command(t_vars *vars, char *input)
{
	if (vars->prompt)
		free(vars->prompt);
	if (!input || !*input)
		return ;
	clean_cmds(vars);
	clean_args(vars);
	clean_tokens(vars);
	free(input);
	vars->pipe = 1;
}

void	quit_terminal(t_vars *vars, t_list *variables, char *input)
{
	int	i;

	i = -1;
	clear_history();
	clean_command(vars, input);
	while (vars->env && vars->env[++i])
		free(vars->env[i]);
	if (vars->env)
		free(vars->env);
	while (vars->var)
	{
		if (vars->var->name)
			free(vars->var->name);
		if (vars->var->content)
			free(vars->var->content);
		free(vars->var);
		vars->var = vars->var->next;
	}
	(void) variables;
	exit(0);
}

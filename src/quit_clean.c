/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:25:38 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/06 14:43:06 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_cmds(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->pipe)
	{
		j = 0;
		while (vars->cmds && vars->cmds[i].cmds && vars->cmds[i].cmds[j])
		{
			free(vars->cmds[i].cmds[j]);
			j++;
		}
		if (vars->cmds && vars->cmds[i].cmds)
			free(vars->cmds[i].cmds);
		i++;
	}
	if (vars->cmds)
	{
		free(vars->cmds);
		vars->cmds = NULL;
	}
}

void	clean_args(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->args && vars->args[i])
	{
		j = 0;
		while (vars->args[i][j])
		{
			free(vars->args[i][j]);
			j++;
		}
		if (vars->args[i])
			free(vars->args[i]);
		i++;
	}
	if (vars->args)
	{
		free(vars->args);
		vars->args = NULL;	
	}
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
		vars->token.tokens = NULL;
	}
}

void	clean_command(t_vars *vars)
{
	if (vars->prompt)
		free(vars->prompt);
	if (!vars->input || !*vars->input)
		return ;
	if (vars->cmds)
		clean_cmds(vars);
	if (vars->args)
		clean_args(vars);
	if (vars->token.tokens)
		clean_tokens(vars);
	free(vars->input);
	vars->pipe = 1;
}

void	quit_terminal(t_vars *vars, int exit_code)
{
	int		i;
	t_list	*temp;

	i = -1;
	clear_history();
	clean_command(vars);
	while (vars->env && vars->env[++i])
		free(vars->env[i]);
	if (vars->env)
		free(vars->env);
/* 	if (vars->exit_char != NULL)
		free (vars->exit_char); */
	while (vars->var)
	{
		if (vars->var->name)
			free(vars->var->name);
		if (vars->var->content)
			free(vars->var->content);
/* 		if (vars->var)
			free(vars->var); */
		if (vars->var->next != NULL)
		{
			temp = vars->var;
			vars->var = vars->var->next;
			free(temp);
		}
		else
		{
			free(vars->var);
			break ;
		}
	}
	exit(exit_code);
}

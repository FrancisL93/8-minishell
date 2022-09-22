/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:25:38 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/20 16:07:09 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_redir(t_vars *vars, int i, int ii)
{
/*  if (vars->inf != NULL)
        free (vars->inf);
    if (vars->outf != NULL)
        free (vars->outf);
    if (vars->outappf != NULL)
        free (vars->outappf); */
	free(vars->args[i][ii]);
	vars->args[i][ii] = NULL;
	free(vars->args[i][ii + 1]);
	vars->args[i][ii + 1] = NULL;
/*     ft_bzero(vars->args[i][ii], ft_strlen(vars->args[i][ii]));
    ii++;
    ft_bzero(vars->args[i][ii], ft_strlen(vars->args[i][ii])); */
}

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
	int	i;
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
	free(vars->prompt);
}
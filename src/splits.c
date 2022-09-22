/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:18:41 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/22 11:38:19 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*subsubsplit(t_vars *vars, int *j)
{
	t_indexes	i;
	int			len;

	i.j = 0;
	i.i = 1;
	len = 0;
	if (!vars->token.tokens[*j] || *j > vars->nb_tokens
		|| !ft_strncmp(vars->token.tokens[*j], "|", 1))
		return (NULL);
	if (vars->token.tokens[*j][0] == 39 || vars->token.tokens[*j][0] == 34)
	{
		if (vars->token.tokens[*j][0] == 39)
			return (split_quotes(vars->token.tokens[*j], vars, i, len));
		else if (vars->token.tokens[*j][0] == 34)
			return (split_db_quotes(vars->token.tokens[*j], vars, i, len));
	}
	i.i = 0;
	return (split_tokens(vars->token.tokens[*j], vars, i, len));
}

char	**subsplit(t_vars *vars, int *j, int index)
{
	int		i;
	char	**cmds;

	i = 0;
	cmds = malloc(sizeof(char *) * (vars->nb_tokens + 1));
	while (1)
	{
		cmds[i] = subsubsplit(vars, j);
		if (cmds[i] == NULL)
		{
			*j += 1;
			break ;
		}
		else
		{
			*j += 1;
			i++;
		}
	}
	ft_retrieve_commands(vars, cmds, i, index);
	return (cmds);
}

void	split_cmds(t_vars *vars)
{
	int		i;
	int		ii;
	int		j;

	i = -1;
	ii = 0;
	j = 0;
	vars->args = malloc(sizeof(char **) * vars->pipe);
	vars->cmds = malloc(sizeof(t_cmds) * vars->pipe);
	while (++i < vars->pipe)
		vars->args[i] = subsplit(vars, &j, i);
	vars->args[vars->pipe] = NULL;
}

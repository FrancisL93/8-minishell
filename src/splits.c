/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:18:41 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/05 10:24:04 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*split_tokens(char *token, t_vars *vars, t_indexes i, int len)
{
	char	*cmnd;
	char	quote;

	quote = token[0];
	if (quote == 34 || quote == 39)
	{
		len = token_len(token, vars, token[0]);
		i.i++;
	}
	else
		len = token_len(token, vars, ' ');
	cmnd = ft_calloc(sizeof(char), len + 1);
	if (!cmnd)
		return (NULL);
	return (split_commands(token, vars, i, cmnd));
}

char	*subsubsplit(t_vars *vars, int *j)
{
	t_indexes	i;
	int			len;

	i.j = 0;
	len = 0;
	if (!vars->token.tokens[*j] || *j > vars->nb_tokens
		|| !ft_strncmp(vars->token.tokens[*j], "|", 1))
		return (NULL);
	i.i = 0;
	return (split_tokens(vars->token.tokens[*j], vars, i, len));
}

char	**subsplit(t_vars *vars, int *j, int index)
{
	t_indexes	i;
	char		**cmds;

	i.i = 0;
	cmds = malloc(sizeof(char *) * vars->nb_tokens + 1);
	while (1)
	{
		cmds[i.i] = subsubsplit(vars, j);
		if (cmds[i.i] == NULL)
		{
			*j += 1;
			break ;
		}
		else
		{
			*j += 1;
			i.i++;
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
	vars->args = malloc(sizeof(char **) * (vars->pipe + 1));
	vars->cmds = malloc(sizeof(t_cmds) * vars->pipe);
	while (++i < vars->pipe)
		vars->args[i] = subsplit(vars, &j, i);
	vars->args[vars->pipe] = NULL;
}

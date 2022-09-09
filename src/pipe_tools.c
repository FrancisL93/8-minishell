/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:43:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/09 15:45:48 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*subsubsplit(t_vars *vars, int *j)
{
	char	*cmd;
	int		i;
	int		len;

	i = 0;
	if (!vars->token.tokens[*j])
		return (NULL);
	len = ft_strlen(vars->token.tokens[*j]);
	cmd = ft_calloc(sizeof(char), len + 1);
	if (*j > vars->nb_tokens)
		return (NULL);
	if (!ft_strncmp(vars->token.tokens[*j], "|", 1))
		return (NULL);
	while (vars->token.tokens[*j][i])
	{
		cmd[i] = vars->token.tokens[*j][i];
		i++;
	}
	return (cmd);
}

char	**subsplit(t_vars *vars, int *j)
{
	int		i;
	char	**cmds;

	i = 0;
	cmds = ft_calloc(sizeof(char *), vars->nb_tokens + 1);
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
	return (cmds);
}

char	***split_cmds(t_vars *vars)
{
	int		i;
	int		ii;
	int		j;
	char	***cmds;

	i = -1;
	ii = 0;
	j = 0;
	cmds = ft_calloc(sizeof(char **), vars->pipe);
	while (++i < vars->pipe)
		cmds[i] = subsplit(vars, &j);
	return (cmds);
}

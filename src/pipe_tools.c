/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:43:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/13 12:01:09 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_retrieve_commands(t_vars *vars, char **cmnd, int i, int ind)
{
	int	j;
	int	ii;

	j = 0;
	ii = 0;
	vars->cmds[ind].index = ind;
	vars->cmds[ind].cmds = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		if (ft_strnstr(cmnd[j], ">", 1)
			|| ft_strnstr(cmnd[j], "<", 1))
			j += 2;
		else
		{
			vars->cmds[ind].cmds[ii] = cmnd[j];
			ii++;
			j++;
		}
	}
	vars->cmds[ind].cmds[ii] = NULL;
}

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

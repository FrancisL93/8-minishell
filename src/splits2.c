/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:43:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/22 10:20:00 by anhebert         ###   ########.fr       */
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
			&& ft_strnstr(cmnd[j + 1], ">", 1))
			j += 3;
		else if (ft_strnstr(cmnd[j], ">", 1)
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

char	*split_db_quotes(char *token, t_vars *vars, t_indexes i, int len)
{
	char	*cmd;
	char	*var;
	t_list	*head;

	token_len(&token[1], vars, token[0], &len);
	cmd = ft_calloc(sizeof(char), len + 1);
	head = vars->var;
	while (token[i.i] != 34)
	{
		i.ii = 0;
		if (token[i.i] == 36)
		{
			var = get_variable(vars, &token[i.i]);
			vars->var = head;
			i.i += dolvar_len(&token[i.i]);
			if (var != NULL)
				while (var[i.ii])
					cmd[i.j++] = var[i.ii++];
		}
		else
			cmd[i.j++] = token[i.i++];
	}
	return (cmd);
}

char	*split_quotes(char *token, t_vars *vars, t_indexes i, int len)
{
	char	*cmd;

	token_len(&token[1], vars, token[0], &len);
	cmd = malloc(sizeof(char) * len + 1);
	while (token[i.i] != 39)
		cmd[i.j++] = token[i.i++];
	return (cmd);
}

char	*split_tokens(char *token, t_vars *vars, t_indexes i, int len)
{
	char	*cmd;
	char	*var;
	t_list	*head;

	token_len(token, vars, token[0], &len);
	if (len == 0)
		return (NULL);
	cmd = ft_calloc(sizeof(char), len + 1);
	head = vars->var;
	while (token[i.i])
	{
		i.ii = 0;
		if (token[i.i] == 34 || token[i.i] == 39)
			i.i++;
		else if (token[i.i] == 36)
		{
			var = get_variable(vars, &token[i.i]);
			vars->var = head;
			i.i += dolvar_len(&token[i.i]);
			if (var != NULL)
				while (var[i.ii])
					cmd[i.j++] = var[i.ii++];
		}
		else
			cmd[i.j++] = token[i.i++];
	}
	return (cmd);
}

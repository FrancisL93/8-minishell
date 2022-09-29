/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:43:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/29 14:18:11 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_quote(t_indexes i, char *token, char sep)
{
	while (token[i.i] != '\0')
	{
		i.i++;
		if (token[i.i] == sep && sep == 34)
			return (2);
		if (token[i.i] == sep && sep == 39)
			return (1);
	}
	return (0);
}

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

char	*split_tokens(char *token, t_vars *vars, t_indexes i, int len)
{
	char	*cmd;
	char	*var;
	char	quote;
	int		is_quote;
	t_list	*head;

	quote = token[0];
	if (quote == 34 || quote == 39)
	{
		len = token_len(&token[1], vars, token[0]);
		i.i++;
	}
	else
		len = token_len(token, vars, ' ');
	cmd = ft_calloc(sizeof(char), len + 1);
	head = vars->var;
	is_quote = ft_is_quote(i, token, token[0]);
	while (token[i.i])
	{
		i.ii = 0;
		if (token[i.i] == 36 && is_quote != 1)
		{
			var = get_variable(vars, &token[i.i]);
			vars->var = head;
			i.i += dolvar_len(&token[i.i]);
			if (var != NULL)
				while (var[i.ii])
					cmd[i.j++] = var[i.ii++];
		}
		else if (quote == 34 && token[i.i] == 34)
		{
			is_quote = 0;
			quote = ' ';
			i.i++;
		}
		else if (quote == 39 && token[i.i] == 39)
		{
			is_quote = 0;
			quote = ' ';
			i.i++;
		}
		else if (quote != 39 && token[i.i] == 39 && is_quote == 0)
		{
			is_quote = ft_is_quote(i, token, 39);
			quote = 39;
			i.i++;
		}
		else if (quote != 34 && token[i.i] == 34 && is_quote == 0)
		{
			is_quote = ft_is_quote(i, token, 34);
			quote = 34;
			i.i++;
		}
		else
			cmd[i.j++] = token[i.i++];
	}
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:43:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/19 13:34:15 by flahoud          ###   ########.fr       */
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

int	dolvar_len(char *token)
{
	int	len;

	len = 1;
	if (token == NULL)
		return (0);
	while (token[len] && token[len] != ' ' && token[len] != 34
		&& token[len] != 36 && token[len] != 39)
		len++;
	return (len);
}

int	token_len(char *token, t_vars *vars, char sep)
{
	int		len;
	int		i;
	t_list	*head;

	len = 0;
	i = 0;
	head = vars->var;
	if (sep == 39)
		while (token[len] != 39)
			len++;
	else
	{
		while (token[i] && token[i] != 34)
		{
			if (token[i] == 36)
			{
				len += dolvar_len(get_variable(vars, &token[len]));
				vars->var = head;
				while (token[i] && token[i] != ' ' && token[i] != 34)
					i++;
			}
			else
			{
				len++;
				i++;
			}
		}
	}
	return (len);
}

char	*split_db_quotes(char *token, t_vars *vars, t_indexes i)
{
	int		len;
	char	*cmd;
	char	*var;
	t_list	*head;

	len = token_len(&token[1], vars, token[0]);
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

char	*split_quotes(char *token, t_vars *vars, t_indexes i)
{
	int		len;
	char	*cmd;

	len = token_len(&token[1], vars, token[0]);
	cmd = malloc(sizeof(char) * len + 1);
	while (token[i.i] != 39)
		cmd[i.j++] = token[i.i++];
	return (cmd);
}

char	*split_tokens(char *token, t_vars *vars, t_indexes i)
{
	int		len;
	char	*cmd;
	char	*var;
	t_list	*head;

	len = token_len(token, vars, token[0]);
	if (len == 0)
		return (NULL);
	cmd = ft_calloc(sizeof(char), len + 1);
	head = vars->var;
	while (token[i.i])
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

char	*subsubsplit(t_vars *vars, int *j)
{
	t_indexes	i;

	i.j = 0;
	i.i = 1;
	if (!vars->token.tokens[*j])
		return (NULL);
	if (*j > vars->nb_tokens)
		return (NULL);
	if (!ft_strncmp(vars->token.tokens[*j], "|", 1))
		return (NULL);
	if (vars->token.tokens[*j][0] == 39 || vars->token.tokens[*j][0] == 34)
	{
		if (vars->token.tokens[*j][0] == 39)
			return (split_quotes(vars->token.tokens[*j], vars, i));
		else if (vars->token.tokens[*j][0] == 34)
			return (split_db_quotes(vars->token.tokens[*j], vars, i));
	}
	i.i = 0;
	return (split_tokens(vars->token.tokens[*j], vars, i));
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

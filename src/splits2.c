/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:43:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/05 15:25:41 by anhebert         ###   ########.fr       */
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

void	ft_retrieve_commands(t_vars *vars, char **cmd, t_indexes i, int ind)
{
	i.j = 0;
	i.ii = 0;
	vars->cmds[ind].index = ind;
	vars->cmds[ind].cmds = malloc(sizeof(char *) * (i.i + 1));
	while (cmd[i.j] != NULL)
	{
		if (cmd[i.j][0] == '>' || cmd[i.j][0] == '<')
		{
			while (cmd[i.j] != NULL && (cmd[i.j][0] == '>'
				|| cmd[i.j][0] == '<'))
				i.j ++;
			if (cmd[i.j])
				i.j++;
		}
		else
		{
			vars->cmds[ind].cmds[i.ii] = ft_strdup(cmd[i.j]);
			i.ii++;
			i.j++;
		}
	}
	vars->cmds[ind].cmds[i.ii] = NULL;
}

void	create_dolvar(t_vars *vars, char *token, char *cmd, t_indexes *i)
{
	char	*var;
	t_list	*head;

	i->ii = 0;
	head = vars->var;
	var = get_variable(vars, &token[i->i]);
	vars->var = head;
	i->i += dolvar_len(&token[i->i]);
	if (var != NULL)
	{
		while (var[i->ii])
		{
			cmd[i->j] = var[i->ii];
			i->j++;
			i->ii++;
		}
	}
}

int	check_quotes(char *quote, char *token, t_indexes *i, int *is_quote)
{
	if ((*quote == 34 && token[i->i] == 34)
		|| (*quote == 39 && token[i->i] == 39))
	{
		*is_quote = 0;
		*quote = ' ';
		i->i++;
	}
	else if (*quote != 39 && token[i->i] == 39 && *is_quote == 0)
	{
		*is_quote = ft_is_quote(*i, token, 39);
		*quote = 39;
		i->i++;
	}
	else if (*quote != 34 && token[i->i] == 34 && *is_quote == 0)
	{
		*is_quote = ft_is_quote(*i, token, 34);
		*quote = 34;
		i->i++;
	}
	else
		return (1);
	return (0);
}

char	*split_commands(char *token, t_vars *vars, t_indexes i, char *cmd)
{
	int		is_quote;
	int		ret;
	t_list	*head;
	char	quote;

	head = vars->var;
	is_quote = ft_is_quote(i, token, token[0]);
	quote = token[0];
	while (token[i.i])
	{
		if (token[i.i] == 36 && !is_space(token[i.i + 1])
			&& token[i.i + 1] != '\0' && token[i.i + 1] != 36
			&& is_quote != 1)
			create_dolvar(vars, token, cmd, &i);
		else if (token[i.i] == 34 || token[i.i] == 39)
		{
			ret = check_quotes(&quote, token, &i, &is_quote);
			if (ret == 1)
				cmd[i.j++] = token[i.i++];
		}
		else
			cmd[i.j++] = token[i.i++];
	}
	return (cmd);
}

/* char	*split_tokens(char *token, t_vars *vars, t_indexes i, int len)
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
		if (token[i.i] == 36 && token[i.i + 1] != ' '
			&& token[i.i + 1] != '\0' && token[i.i + 1] != 36
			&& is_quote != 1)
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
} */

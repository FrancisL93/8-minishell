/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:29:02 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/27 08:47:02 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	inquotes(int i, char *input, char c, t_vars *vars)
{
	int	ii;

	ii = i;
	while (input[i])
	{
		i++;
		if (input[i] == c)
		{
			vars->nb_tokens++;
			return (i);
		}
	}
	return (ii);
}

void	count_nb_tokens(char *input, t_vars *vars, t_indexes ind)
{
	vars->nb_tokens = 0;
	while (input[ind.i])
	{
		if (input[ind.i] == '<' || input[ind.i] == '>' || input[ind.i] == '|')
		{
			vars->nb_tokens++;
			ind.i++;
		}
		else if (input[ind.i] == 39 || input[ind.i] == 34)
			ind.i = inquotes(ind.i + 1, input, input[ind.i], vars);
		else if (input[ind.i] == ' ')
			ind.i++;
		else
		{
			vars->nb_tokens++;
			while (input[ind.i] != ' ' && input[ind.i] != 39
				&& input[ind.i] != '"' && input[ind.i] != '<'
				&& input[ind.i] != '>' && input[ind.i] != '|')
			{
				ind.i++;
				if (input[ind.i] == '=')
					var_len(&ind, input);
				if (input[ind.i] == '\0')
					break ;
			}
		}
	}
}

void	tokenizer(t_vars *vars, t_indexes *ind, char *input)
{
	int	x;

	x = 0;
	vars->token_len = ind->i - ind->ii;
	vars->token.tokens[ind->j] = ft_calloc(sizeof(char), vars->token_len + 2);
	while (ind->ii <= ind->i)
	{
		vars->token.tokens[ind->j][ind->jj] = input[ind->ii];
		ind->ii++;
		ind->jj++;
	}
	ind->i++;
	ind->j++;
}

void	new_token(char *in, t_vars *vars, t_indexes i)
{
	while (in[i.i])
	{
		i.ii = i.i;
		i.jj = 0;
		if (in[i.i] == '<' || in[i.i] == '>' || in[i.i] == '|')
			tokenizer(vars, &i, in);
		else if (in[i.i] == 39 || in[i.i] == 34)
		{
			i.i += inquoteslen(i.i + 1, in, in[i.i]);
			if (i.i != i.ii)
				tokenizer(vars, &i, in);
			else
				i.i++;
		}
		else if (in[i.i] == ' ')
			i.i++;
		else if (in[i.i] != '\0')
		{
			while (in[i.i + 1] != ' ' && in[i.i + 1] != 39 && in[i.i + 1] != '"'
				&& in[i.i + 1] != '\0' && in[i.i + 1] != '<'
				&& in[i.i + 1] != '>' && in[i.i + 1] != '|')
			{
				i.i++;
				if (in[i.i] == '=')
					var_len(&i, in);
			}
			tokenizer(vars, &i, in);
		}
	}
}

void	lexer(char *input, t_vars *vars)
{
	t_indexes	indexes;
	int			j;

	j = 0;
	indexes.i = 0;
	indexes.ii = 0;
	indexes.j = 0;
	indexes.jj = 0;
	if (!ft_strncmp("exit", input, 4))
		quit_terminal(vars, vars->var);
	if (input && *input)
		add_history(input);
	vars->token_len = 0;
	count_nb_tokens(input, vars, indexes);
	vars->token.tokens = malloc(sizeof(char *) * (vars->nb_tokens + 1));
	new_token(input, vars, indexes);
	vars->token.tokens[vars->nb_tokens] = NULL;
	while (vars->token.tokens[indexes.i])
		if (!ft_strncmp(vars->token.tokens[indexes.i++], "|", 1))
			vars->pipe++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:07 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/22 10:03:02 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Calcule le nombre de tokens se trouvant entre "" ou ''
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

// Calcule la longueur des tokens
int	inquoteslen(t_vars *vars, int i, char *input, char c)
{
	int		ii;
	int		varlen;
	char	*var;

	ii = i;
	varlen = 0;
	while (input[++i])
	{
		if (input[i] == c)
			return (varlen);
		if (input[i] == '$')
		{
			var = get_variable(vars, &input[i]);
			varlen += ft_strlen(&var[ft_strichr(var, '=')]);
			while (input[i] && input[i] != ' ')
				i++;
		}
		varlen++;
	}
	return (0);
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
		else if (input[ind.i] == 39 || input[ind.i] == '"')
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
				if (input[ind.i] == '\0')
					break ;
			}
		}
	}
}

void	tokenizer(t_vars *vars, t_indexes *ind, char *input)
{
	char	*var;
	int		var_cont;

	vars->token_len = ind->i - ind->ii;
	vars->token.tokens[ind->j] = ft_calloc(sizeof(char), vars->token_len + 2);
	while (ind->ii <= ind->i)
	{
		if (input[ind->ii] == '$')
		{
			var = get_variable(vars, &input[ind->ii]);
			var_cont = ft_strichr(var, '=') + 1;
			while (var && var[var_cont])
				vars->token.tokens[ind->j][ind->jj++] = var[var_cont++];
			while (input[ind->ii] != ' ')
				ind->ii++;
		}
		else
			vars->token.tokens[ind->j][ind->jj++] = input[ind->ii++];
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
		else if (in[i.i] == 39 || in[i.i] == '"')
		{
			i.i = inquoteslen(vars, i.i + 1, in, in[i.i]);
			if (i.i != 0)
				tokenizer(vars, &i, in);
			else
				i.i = i.ii + 1;
		}
		else if (in[i.i] == ' ')
			i.i++;
		else
		{
			while (in[i.i + 1] != ' ' && in[i.i + 1] != 39 && in[i.i + 1] != '"'
				&& in[i.i] != '\0' && in[i.i + 1] != '<' && in[i.i + 1] != '>'
				&& in[i.i + 1] != '|')
				i.i++;
			tokenizer(vars, &i, in);
		}
	}
}

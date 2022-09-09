/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:29:02 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/09 10:34:29 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	ii = i;
	varlen = 0;
	while (input[++i])
	{
		if (input[i] == c)
			return (varlen);
		varlen++;
	}
	if (vars)
		return (0);
	return (0);
}

//Compte le nombre de 'tokens' se trouvant entre double quotes, single quotes et espaces
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

// Crée les tokens
void	tokenizer(t_vars *vars, t_indexes *ind, char *input)
{
	vars->token_len = ind->i - ind->ii;
	vars->token.tokens[ind->j] = ft_calloc(sizeof(char), vars->token_len + 2);
	while (ind->ii <= ind->i)
			vars->token.tokens[ind->j][ind->jj++] = input[ind->ii++];
	ind->i++;
	ind->j++;
}

// Sépare les tokens selon les '', "", ou ' '
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

void	lexer(char *input, t_vars *vars)
{
	t_indexes	indexes;
	int			j;

	j = 0;
	indexes.i = 0;
	indexes.ii = 0;
	indexes.j = 0;
	indexes.jj = 0;
	vars->token_len = 0;
	count_nb_tokens(input, vars, indexes);
	vars->token.tokens = malloc(sizeof(char *) * (vars->nb_tokens + 1));
	new_token(input, vars, indexes);
	vars->token.tokens[vars->nb_tokens] = NULL;
	while (vars->token.tokens[indexes.i])
		if (!ft_strncmp(vars->token.tokens[indexes.i++], "|", 1))
			vars->pipe++;
}

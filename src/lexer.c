/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:29:02 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/14 10:13:51 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

//Create the tokens
void	tokenizer(t_vars *vars, t_indexes *ind)
{
	ind->jj = 0;
	vars->token_len = ind->i - ind->ii;
	vars->token.tokens[ind->j] = ft_calloc(sizeof(char), vars->token_len + 2);
	if (!vars->token.tokens[ind->j])
		return ;
	while (ind->ii < ind->i)
	{
		vars->token.tokens[ind->j][ind->jj] = vars->input[ind->ii];
		ind->ii++;
		ind->jj++;
	}
	ind->jj++;
	if (vars->input[ind->i] != '\0')
		ind->j++;
}

void	check_if_token(t_vars *vars, t_indexes *i)
{
	while (vars->input[i->i] != '\0' && !is_space(vars->input[i->i])
		&& vars->input[i->i] != '<' && vars->input[i->i] != '>'
		&& vars->input[i->i] != '|')
	{
		i->i++;
		if (vars->input[i->i] == '=')
			var_len(i, vars->input);
		else if (vars->input[i->i] == 34 || vars->input[i->i] == 39)
			i->i += inquoteslen(i->i + 1, vars->input, vars->input[i->i]) + 1;
		if (vars->input[i->i] == '\0' || is_space(vars->input[i->i])
			|| vars->input[i->i] == '<' || vars->input[i->i] == '>'
			|| vars->input[i->i] == '|')
			tokenizer(vars, i);
	}
}

//Check when to split the tokens
void	new_token(t_vars *vars, t_indexes i)
{
	while (vars->input[i.i])
	{
		i.ii = i.i;
		if (vars->input[i.i] == 39 || vars->input[i.i] == 34)
		{
			i.i += inquoteslen(i.i + 1, vars->input, vars->input[i.i]) + 1;
			if (vars->input[i.i] == '\0' || is_space(vars->input[i.i])
				|| vars->input[i.i] == '<' || vars->input[i.i] == '>'
				|| vars->input[i.i] == '|')
				tokenizer(vars, &i);
		}
		if (vars->input[i.i] != '\0' && !is_space(vars->input[i.i]))
			check_if_token(vars, &i);
		if (is_space(vars->input[i.i]) || vars->input[i.i] == '<'
			|| vars->input[i.i] == '>' || vars->input[i.i] == '|')
		{
			i.ii = i.i;
			i.i++;
			if (vars->input[i.i - 1] == '<' || vars->input[i.i - 1] == '>'
				|| vars->input[i.i - 1] == '|')
				tokenizer(vars, &i);
		}
	}
}

//Split input into tokens and add readline history
int	lexer(t_vars *vars)
{
	t_indexes	indexes;

	indexes.i = 0;
	indexes.ii = 0;
	indexes.j = 0;
	indexes.jj = 0;
	vars->nb_tokens = 0;
	if (vars->input && *vars->input)
		add_history(vars->input);
	vars->token_len = 0;
	if (count_nb_tokens(vars, indexes) == 1 || vars->nb_tokens == 0)
		return (1);
	vars->token.tokens = malloc(sizeof(char *) * (vars->nb_tokens + 1));
	if (!vars->token.tokens)
		return (1);
	new_token(vars, indexes);
	vars->token.tokens[vars->nb_tokens] = NULL;
	while (vars->token.tokens[indexes.i])
	{
		if (!ft_strncmp(vars->token.tokens[indexes.i++], "|", 1))
			vars->pipe++;
	}
	return (0);
}

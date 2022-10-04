/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:29:02 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/04 13:41:37 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	tokenizer(t_vars *vars, t_indexes *ind, char *input)
{
	ind->jj = 0;
	vars->token_len = ind->i - ind->ii;
	vars->token.tokens[ind->j] = ft_calloc(sizeof(char), vars->token_len + 2);
	if (!vars->token.tokens[ind->j])
		return ;
	while (ind->ii < ind->i)
	{
		vars->token.tokens[ind->j][ind->jj] = input[ind->ii];
		ind->ii++;
		ind->jj++;
	}
	ind->jj++;
	if (input[ind->i] != '\0')
		ind->j++;
}

void	check_if_token(char *in, t_vars *vars, t_indexes *i)
{
	while (in[i->i] != '\0' && in[i->i] != ' ' && in[i->i] != '<'
		&& in[i->i] != '>' && in[i->i] != '|')
	{
		i->i++;
		if (in[i->i] == '=')
			var_len(i, in);
		else if (in[i->i] == 34 || in[i->i] == 39)
			i->i += inquoteslen(i->i + 1, in, in[i->i]) + 1;
		if (in[i->i] == '\0' || in[i->i] == ' ' || in[i->i] == '<'
			|| in[i->i] == '>' || in[i->i] == '|')
			tokenizer(vars, i, in);
	}
}

void	new_token(char *in, t_vars *vars, t_indexes i)
{
	while (in[i.i])
	{
		i.ii = i.i;
		if (in[i.i] == 39 || in[i.i] == 34)
		{
			i.i += inquoteslen(i.i + 1, in, in[i.i]) + 1;
			if (in[i.i] == '\0' || in[i.i] == ' ' || in[i.i] == '<'
				|| in[i.i] == '>' || in[i.i] == '|')
				tokenizer(vars, &i, in);
		}
		else if (in[i.i] != '\0' && in[i.i] != ' ')
			check_if_token(in, vars, &i);
		if (in[i.i] == ' ' || in[i.i] == '<' || in[i.i] == '>'
			|| in[i.i] == '|')
		{
			i.ii = i.i;
			i.i++;
			if (in[i.i - 1] == '<' || in[i.i - 1] == '>' || in[i.i - 1] == '|')
				tokenizer(vars, &i, in);
		}
	}
}

int	lexer(char *input, t_vars *vars)
{
	t_indexes	indexes;

	indexes.i = 0;
	indexes.ii = 0;
	indexes.j = 0;
	indexes.jj = 0;
	vars->nb_tokens = 0;
	if (!ft_strncmp("exit", input, 4))
		quit_terminal(vars, vars->var, input);
	if (input && *input)
		add_history(input);
	vars->token_len = 0;
	if (count_nb_tokens(input, vars, indexes) == 1 || vars->nb_tokens == 0)
		return (1);
	vars->token.tokens = malloc(sizeof(char *) * (vars->nb_tokens + 1));
	if (!vars->token.tokens)
		return (1);
	new_token(input, vars, indexes);
	vars->token.tokens[vars->nb_tokens] = NULL;
	while (vars->token.tokens[indexes.i])
	{
		if (!ft_strncmp(vars->token.tokens[indexes.i++], "|", 1))
			vars->pipe++;
	}
	return (0);
}

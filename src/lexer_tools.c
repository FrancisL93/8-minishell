/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:13:12 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/05 11:55:43 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_meta(char *in, int i)
{
	if (in[i + 1] != '\0' && in[i] == '<')
	{
		if (in[i + 1] == '>' || in[i + 1] == '|')
			return (1);
		else if (in[i + 2] && in[i + 1] == '<'
			&& (in[i + 2] == '>' || in [i + 2] == '|'
				|| in[i + 2] == '<'))
			return (1);
	}
	else if (in[i + 1] != '\0' && in[i] == '>')
	{
		if (in[i + 1] == '<' || in[i + 1] == '|')
			return (1);
		else if (in[i + 2] && in[i + 1] == '>' && (in[i + 2] == '>'
				|| in [i + 2] == '|' || in[i + 2] == '<'))
			return (1);
	}
	else if (in[i + 1] != '\0' && in[i] == '|')
	{
		if (in[i + 1] == '|')
			return (1);
	}
	return (0);
}

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

void	check_if_is_token(char *in, t_vars *vars, t_indexes *i)
{
	while (!is_space(in[i->i]) && in[i->i] != '\0' && in[i->i] != '<'
		&& in[i->i] != '>' && in[i->i] != '|')
	{
		i->i++;
		if (in[i->i] == '=')
			var_len(i, in);
		else if (in[i->i] == 34 || in[i->i] == 39)
			i->i += inquoteslen(i->i + 1, in, in[i->i]) + 1;
		if (in[i->i] == '\0' || is_space(in[i->i]) || in[i->i] == '<'
			|| in[i->i] == '>' || in[i->i] == '|')
			vars->nb_tokens++;
	}
}

void	check_if_is_token2(char *in, t_vars *vars, t_indexes *i)
{
	int	ii;

	ii = i->i;
	i->i += inquoteslen(i->i + 1, in, in[i->i]) + 1;
	if (ii + 1 == i->i)
	{
		i += 1;
		return ;
	}
	if (in[i->i] == '\0' || is_space(in[i->i]) || in[i->i] == '<'
		|| in[i->i] == '>' || in[i->i] == '|')
		vars->nb_tokens++;
}

int	count_nb_tokens(char *in, t_vars *vars, t_indexes i)
{
	while (in[i.i])
	{
		if (in[i.i] == 39 || in[i.i] == 34)
			check_if_is_token2(in, vars, &i);
		else if (in[i.i] != '\0' && !is_space(in[i.i]))
			check_if_is_token(in, vars, &i);
		if (is_space(in[i.i]))
				i.i++;
		else if (in[i.i] == '<' || in[i.i] == '>' || in[i.i] == '|')
		{
			if (check_meta(in, i.i) == 1)
			{
				printf("minishell: syntax error near unexpected token\n");
				return (1);
			}
			vars->nb_tokens ++;
			i.i++;
		}
	}
	return (0);
}

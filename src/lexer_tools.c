/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:13:12 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/03 09:14:54 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_meta(char *in, int i)
{
	if (in[i + 1] && in[i] == '<')
	{
		if (in[i + 1] == '>' || in[i + 1] == '|')
			return (1);
		else if (in[i + 2] && (in[i + 2] == '>' || in [i + 2] == '|'
				|| in[i + 2] == '<'))
			return (1);
	}
	else if (in[i + 1] && in[i] == '>')
	{
		if (in[i + 1] == '<' || in[i + 1] == '|')
			return (1);
		else if (in[i + 2] && (in[i + 2] == '>' || in [i + 2] == '|'
				|| in[i + 2] == '<'))
			return (1);
	}
	else if (in[i + 1] && in[i] == '|')
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

int	count_nb_tokens(char *in, t_vars *vars, t_indexes i)
{
	vars->nb_tokens = 0;
	while (in[i.i])
	{
		if (in[i.i] == 39 || in[i.i] == 34)
		{
			i.i += inquoteslen(i.i + 1, in, in[i.i]) + 1;
			if (in[i.i] == '\0' || in[i.i] == ' ' || in[i.i] == '<'
				|| in[i.i] == '>' || in[i.i] == '|')
				vars->nb_tokens++;
		}
		else if (in[i.i] != '\0' && in[i.i] != ' ')
		{
			while (in[i.i] != ' ' && in[i.i] != '\0' && in[i.i] != '<'
				&& in[i.i] != '>' && in[i.i] != '|')
			{
				i.i++;
				if (in[i.i] == '=')
					var_len(&i, in);
				else if (in[i.i] == 34 || in[i.i] == 39)
					i.i += inquoteslen(i.i + 1, in, in[i.i]) + 1;
				if (in[i.i] == '\0' || in[i.i] == ' ' || in[i.i] == '<'
					|| in[i.i] == '>' || in[i.i] == '|')
					vars->nb_tokens++;
			}
		}
		if (in[i.i] == '\0' || in[i.i] == ' ')
		{
			if (in[i.i] != '\0')
				i.i++;
		}
		else if (in[i.i] == '<' || in[i.i] == '>'
			|| in[i.i] == '|')
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

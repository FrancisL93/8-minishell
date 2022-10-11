/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:13:12 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/11 10:43:46 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Filter the meta characters and validate
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

int	inquotes(int i, char c, t_vars *vars)
{
	int	ii;

	ii = i;
	while (vars->input[i])
	{
		i++;
		if (vars->input[i] == c)
		{
			vars->nb_tokens++;
			return (i);
		}
	}
	return (ii);
}

//Check normal tokens not in quotes
void	check_if_is_token(t_vars *vars, t_indexes *i)
{
	while (!is_space(vars->input[i->i]) && vars->input[i->i] != '\0'
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
			vars->nb_tokens++;
	}
}

//While in quotes " " or ' '
void	check_if_is_token2(t_vars *vars, t_indexes *i)
{
	int	ii;

	ii = i->i;
	i->i += inquoteslen(i->i + 1, vars->input, vars->input[i->i]) + 1;
	if (ii + 1 == i->i)
	{
		i += 1;
		return ;
	}
	if (vars->input[i->i] == '\0' || is_space(vars->input[i->i])
		|| vars->input[i->i] == '<' || vars->input[i->i] == '>'
		|| vars->input[i->i] == '|')
		vars->nb_tokens++;
}

int	count_nb_tokens(t_vars *vars, t_indexes i)
{
	while (vars->input[i.i])
	{
		if (vars->input[i.i] == 39 || vars->input[i.i] == 34)
			check_if_is_token2(vars, &i);
		else if (vars->input[i.i] != '\0' && !is_space(vars->input[i.i]))
			check_if_is_token(vars, &i);
		if (is_space(vars->input[i.i]))
				i.i++;
		else if (vars->input[i.i] == '<' || vars->input[i.i] == '>'
			|| vars->input[i.i] == '|')
		{
			if (check_meta(vars->input, i.i) == 1)
			{
				printf("minishell: syntax error");
				printf(" near unexpected token `newline'\n");
				return (1);
			}
			vars->nb_tokens ++;
			i.i++;
		}
	}
	return (0);
}

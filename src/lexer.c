/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:09:19 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/30 12:05:59 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	inquoteslen(int i, char *input, char c, t_vars *vars)
{
	int	ii;

	ii = i;
	while (input[i] != c)
	{
		i++;
		if (input[i] == '\0')
			return (ii);
	}
	vars->nb_tokens++;
	return (i);
}
/* 
int	token_len(int len, char *input, char c)
{
	
} */

//Compte le nombre de 'tokens' se trouvant entre double quotes, single quotes et espaces
void	count_nb_tokens(char *input, t_vars *vars)
{
	int	i;

	i = 0;
	vars->nb_tokens = 0;
	while (input[i])
	{
		if (input[i] == 39 || input[i] == '"')
			i = inquoteslen(i + 1, input, input[i], vars) + 1;
		else if (input[i] == ' ')
			i++;
		else
		{
			vars->nb_tokens++;
			while (input[i] != ' ' && input[i] != 39 && input[i] != '"')
			{
				i++;
				if (input[i] == '\0')
					break ;
			}
		}
	}
}

/* char	*new_token(char *input)
{
	
} */

void	lexer(char *input, t_vars *vars)
{
	int	i;

	i = 0;
	count_nb_tokens(input, vars);
	vars->token.tokens = malloc(sizeof(char *) * vars->nb_tokens);
/* 	while (i < vars->nb_tokens)
	{
		vars->token.tokens[i] = new_token(input);
		i++;
	} */
}

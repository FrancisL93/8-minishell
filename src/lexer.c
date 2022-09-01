/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:09:19 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/01 11:30:33 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	lexer(char *input, t_vars *vars)
{
	t_indexes	indexes;

	indexes.i = 0;
	indexes.ii = 0;
	indexes.j = 0;
	indexes.jj = 0;
	vars->token_len = 0;
	count_nb_tokens(input, vars, indexes);
	vars->token.tokens = malloc(sizeof(char *) * vars->nb_tokens + 1);
	new_token(input, vars, indexes);
	vars->token.tokens[vars->nb_tokens] = NULL;
}

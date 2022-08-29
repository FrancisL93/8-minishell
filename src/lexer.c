/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:09:19 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/19 13:48:31 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer(char *input)
{
	int	j;

	j = 0;
	while (input[j])
	{
		if (input[j] == '"')
		{
			j++;
			while (input[j] != '"')
			{
				printf("%c", input[j]);
				j++;
				if (input[j] == '"')
				{
					j++;
					printf("\n");
					break ;
				}
			}
		}
		else if (input[j] == ' ')
			j++;
		else
		{
			while (input[j] != ' ')
			{
				printf("%c", input[j]);
				j++;
				if (input[j] == ' ' || input[j] == '\0')
				{
					j++;
					printf("\n");
					break ;
				}
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:09:19 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/29 16:47:08 by flahoud          ###   ########.fr       */
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

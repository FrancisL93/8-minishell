/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:57:27 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/04 12:17:22 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_str_len(const char *str)
{
	int	size;

	size = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[size])
		size++;
	return (size);
}

int	dolvar_len(char *token)
{
	int	len;

	len = 1;
	if (token == NULL)
		return (0);
	while (token[len] && token[len] != ' ' && token[len] != 34
		&& token[len] != 36 && token[len] != 39)
		len++;
	return (len);
}

int	inquoteslen(int i, char *input, char c)
{
	int		varlen;

	varlen = 1;
	while (input[i])
	{	
		if (input[i] == c)
			return (varlen);
		varlen++;
		i++;
	}
	return (0);
}

void	var_len(t_indexes *i, char *in)
{
	while (in[i->i + 1] != '\0' && in[i->i + 1] != ' ')
	{
		i->i++;
		if (in[i->i] == 34)
		{
			i->i++;
			i->i += inquoteslen(i->i, in, 34);
		}
		if (in[i->i] == 39)
		{
			i->i++;
			i->i += inquoteslen(i->i, in, 39);
		}
	}
}

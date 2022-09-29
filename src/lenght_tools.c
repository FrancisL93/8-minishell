/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:57:27 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/29 14:07:33 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	ft_str_len(const char *str)
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

int	token_len(char *token, t_vars *vars, char sep)
{
	t_indexes	i;
	t_list		*head;
	int			is_quote;
	int			len;

	i.i = 0;
	len = 0;
	head = vars->var;
	if (sep == 34 || sep == 39)
		i.i++;
	is_quote = ft_is_quote(i, token, token[0]);
	while (token[i.i])
	{
		i.ii = 0;
		if (token[i.i] == 36 && is_quote != 1)
		{
			len += dolvar_len(&token[i.i]);
			i.i += dolvar_len(&token[i.i]);
			vars->var = head;
		}
		else if (sep == 34 && token[i.i] == 34)
		{
			is_quote = 0;
			sep = ' ';
			i.i++;
		}
		else if (sep == 39 && token[i.i] == 39)
		{
			is_quote = 0;
			sep = ' ';
			i.i++;
		}
		else if (sep != 39 && token[i.i] == 39 && is_quote == 0)
		{
			is_quote = ft_is_quote(i, token, 39);
			sep = 39;
			i.i++;
		}
		else if (sep != 34 && token[i.i] == 34 && is_quote == 0)
		{
			is_quote = ft_is_quote(i, token, 34);
			sep = 34;
			i.i++;
		}
		else
		{
			len ++;
			i.i++;
		}
	}
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

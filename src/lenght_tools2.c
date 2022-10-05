/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:16:55 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/05 11:37:54 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/minishell.h"

void	commands_len(char *tok, t_vars *vars, t_indexes i, int *len)
{
	int		quote_ret[2];
	t_list	*head;
	char	quote;

	head = vars->var;
	quote_ret[0] = ft_is_quote(i, tok, tok[0]);
	quote = tok[0];
	while (tok[i.i])
	{
		if (tok[i.i] == 36 && !is_space(tok[i.i + 1]) && tok[i.i + 1] != '\0'
			&& tok[i.i + 1] != 36 && quote_ret[0] != 1)
		{
			*len += ft_str_len(get_variable(vars, &tok[i.i]));
			i.i += dolvar_len(&tok[i.i]);
			vars->var = head;
		}
		else if ((tok[i.i] == 34 || tok[i.i] == 39) && quote_ret[1] != 1)
			quote_ret[1] = check_quotes(&quote, tok, &i, &quote_ret[0]);
		else
		{
			quote_ret[1] = 0;
			*len += 1;
			i.i++;
		}
	}
}

int	token_len(char *token, t_vars *vars, char sep)
{
	t_indexes	i;
	int			len;

	i.i = 0;
	len = 0;
	if (sep == 34 || sep == 39)
		i.i++;
	commands_len(token, vars, i, &len);
	return (len);
}

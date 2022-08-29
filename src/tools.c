/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:48:08 by flahoud           #+#    #+#             */
/*   Updated: 2022/08/29 16:48:15 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*tolower_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] >= 65 && str[i] <= 90)
			str[i] += 32;
	return (str);
}

char	*get_cmd(char *input)
{
	int		i;
	int		j;
	char	*cmd;

	i = 2;
	j = 0;
	cmd = calloc(sizeof(char), ft_strlen(input) - 2);
	while (input[++i])
	{
		cmd[j] = input[i];
		j++;
	}
	return (cmd);
}

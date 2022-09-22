/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:49:30 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/22 11:38:07 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_flag(char *flag)
{
	int	i;

	i = 0;
	while (flag[i])
	{
		if (flag[0] != '-')
			return (0);
		i++;
		if (flag[1] != 'n')
			return (0);
		i++;
		if (flag[2] == '\0')
			return (1);
		if (flag[2] != 'n' && flag[2] != ' ')
			return (0);
		while (flag[i] == 'n')
		{
			i++;
			if (flag[i] == ' ' || flag[i] == '\0')
				return (1);
		}
	}
	return (0);
}

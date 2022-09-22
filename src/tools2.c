/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:57:27 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/20 14:58:01 by flahoud          ###   ########.fr       */
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

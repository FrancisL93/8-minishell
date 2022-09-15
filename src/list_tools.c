/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:30:08 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/15 09:54:53 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*ft_lst_new(void *content, void *name)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->name = name;
	new->next = NULL;
	return (new);
}

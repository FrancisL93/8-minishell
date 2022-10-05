/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:30:08 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/05 16:04:29 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_lst_add_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

t_list	*ft_lst_new(void *value, void *var)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	if (!value || value == NULL)
		new->content = NULL;
	else
		new->content = (char *)value;
	new->name = (char *)var;
	new->next = NULL;
	return (new);
}

char	*ft_str_dup(const char *str)
{
	int		i;	
	char	*dest;

	if (!str || !str[0])
		return (NULL);
	dest = malloc(ft_strlen(str) + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

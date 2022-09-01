/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:58:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/01 14:16:45 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Free tout, les appels de fonctions sans retour qui utilse des pointeurs doivent être free!
void	quit(t_vars *vars)
{
	if (vars)
		exit(0);
}
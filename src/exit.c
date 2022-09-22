/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:58:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/06 14:27:37 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Free tout, les appels de fonctions sans retour qui utilse des pointeurs doivent être free!
void	quit_terminal(t_vars *vars, t_list *variables)
{
	int	i;

	i = -1;
	clear_history();
	while (vars->env[++i])
		free(vars->env[i]);
	free(vars->env);
	free(variables);
	free(vars->prompt);
	exit(0);
}

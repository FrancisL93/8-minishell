/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:22:33 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/01 13:40:30 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_built_in(t_vars *vars, int i)
{
	if (ft_strcmp(vars->cmds[i].cmds[0], "echo") == 0)
		echo_built(vars, i);
	else if (ft_strcmp(vars->cmds[i].cmds[0], "pwd") == 0)
		print_path();
	else if (ft_strcmp(vars->cmds[i].cmds[0], "env") == 0)
		print_env(vars);
	else
		return (0);
	return (1);
}

int	check_export(t_vars *vars, int i)
{
	if (ft_strcmp(vars->cmds[i].cmds[0], "export") == 0)
		export(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

int	check_unset(t_vars *vars, int i)
{
	if (ft_strcmp(vars->cmds[i].cmds[0], "unset") == 0)
		unset(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

int	check_cd(t_vars *vars, int i)
{
	if (ft_strcmp(vars->cmds[i].cmds[0], "cd") == 0)
		cd(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

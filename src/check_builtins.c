/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:22:33 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/22 10:23:08 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_built_in(t_vars *vars, int i)
{
	if (!ft_strncmp(vars->cmds[i].cmds[0], "echo", 4))
		echo(vars, i);
	else if (!ft_strncmp(vars->cmds[i].cmds[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(vars->cmds[i].cmds[0], "export", 6))
		return (1);
	else if (!ft_strncmp(vars->cmds[i].cmds[0], "pwd", 3))
		print_path();
	else if (!ft_strncmp(vars->cmds[i].cmds[0], "env", 3))
		print_env(vars);
	else
		return (0);
	return (1);
}

int	check_export(t_vars *vars, int i)
{
	if (!ft_strncmp(vars->cmds[i].cmds[0], "export", 6))
		export(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

int	check_unset(t_vars *vars, int i)
{
	if (!ft_strncmp(vars->cmds[i].cmds[0], "unset", 5))
		unset(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

int	check_cd(t_vars *vars, int i)
{
	if (!ft_strncmp(vars->cmds[i].cmds[0], "cd", 2))
		cd(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

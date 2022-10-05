/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:22:33 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/05 16:24:11 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_built_in(t_vars *vars, int i, int ret)
{
	if (ret < 1 && vars->pipe == 1)
		ret = check_exit(vars, i);
	if (ret < 1 && vars->pipe == 1)
		ret = check_unset(vars, i);
	if (ret < 1 && vars->pipe == 1)
		ret = check_export(vars, i);
	if (ret < 1 && vars->pipe == 1)
		ret = check_cd(vars, i);
	if (vars->cmds->cmds[0] && ft_strcmp(vars->cmds[i].cmds[0], "echo") == 0)
		echo_built(vars, i);
	else if (vars->cmds->cmds[0] && ft_strcmp(vars->cmds[i].cmds[0],
			"pwd") == 0)
		print_path();
	else if (vars->cmds->cmds[0] && ft_strcmp(vars->cmds[i].cmds[0],
			"env") == 0)
		print_env(vars);
	else
		return (0);
	return (1);
}

int	check_export(t_vars *vars, int i)
{
	int	j;

	j = 1;
	if (ft_strcmp(vars->cmds[i].cmds[0], "export") == 0)
	{
		while (vars->cmds[i].cmds[j] != NULL)
		{
			export(vars, vars->cmds[i].cmds[j]);
			j++;
		}
	}
	else
		return (0);
	return (1);
}

int	check_unset(t_vars *vars, int i)
{
	int	j;

	j = 1;
	if (ft_strcmp(vars->cmds[i].cmds[0], "unset") == 0)
	{
		while (vars->cmds[i].cmds[j])
		{
			unset(vars, vars->cmds[i].cmds[j]);
			j++;
		}
	}
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

int	check_exit(t_vars *vars, int i)
{
	if (ft_strcmp(vars->cmds[i].cmds[0], "exit") == 0)
		ft_exit(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

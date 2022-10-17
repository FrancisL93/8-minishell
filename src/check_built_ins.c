/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:22:33 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/17 10:32:57 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Execute built-in in child or before depending on check
int	check_built_in(t_vars *vars, int i, int check)
{
	int	ret;

	ret = 0;
	if (ret < 1 && vars->pipe == 1)
		ret = check_exit(vars, i);
	if (ret < 1 && vars->pipe == 1)
		ret = check_unset(vars, i);
	if (ret < 1 && vars->pipe == 1)
		ret = check_export(vars, i);
	if (ret < 1 && vars->pipe == 1)
		ret = check_cd(vars, i);
	if (ret < 1 && vars->cmds->cmds[0] && check != 1
		&& ft_strcmp(vars->cmds[i].cmds[0], "echo") == 0)
		ret = echo_built(vars, i);
	if (ret < 1 && vars->cmds->cmds[0] && check != 1
		&& ft_strcmp(vars->cmds[i].cmds[0],
			"pwd") == 0)
		ret = print_path();
	if (ret < 1 && vars->cmds->cmds[0] && check != 1
		&& ft_strcmp(vars->cmds[i].cmds[0],
			"env") == 0)
		ret = print_env(vars);
	if (ret == 1 && check != 1)
		close_fds(vars, 1);
	return (ret);
}

int	check_export(t_vars *vars, int i)
{
	int	j;

	j = 1;
	if (ft_strcmp(vars->cmds[i].cmds[0], "export") == 0)
	{
		while (vars->cmds[i].cmds[j] != NULL)
		{
			export(vars, ft_strdup(vars->cmds[i].cmds[j]));
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
	{
		printf("exit\n");
		close_fds(vars, 1);
		if (vars->cmds[i].cmds[1] == NULL)
			quit_terminal(vars, 0);
		ft_exit(vars, vars->cmds[i].cmds[1]);
	}
	else
		return (0);
	return (1);
}

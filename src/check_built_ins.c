/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:22:33 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/05 14:53:26 by anhebert         ###   ########.fr       */
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

void	ft_exit(t_vars *vars, char *exit_status)
{
	int	i;

	i = 0;
	while (exit_status[i])
	{
		if (!ft_isdigit(exit_status[i]))
		{
			printf("exit: %s: numeric argument required\n", exit_status);
			quit_terminal(vars, 255);
		}
		i++;
		if (exit_status[i] == '\0')
			add_exit(vars, ft_atoi(exit_status));
	}
	quit_terminal(vars, ft_atoi(exit_status));
}

int	check_exit(t_vars *vars, int i)
{
	if (ft_strcmp(vars->cmds[i].cmds[0], "exit") == 0)
		ft_exit(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:18:51 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/17 11:09:22 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/minishell.h"

int	search_infile(t_vars *vars, int i, int *ii)
{
	if (vars->args[i][*ii] && vars->args[i][*ii][0] == '<')
	{
		if (vars->args[i][*ii + 1] && vars->args[i][*ii + 1][0] == '<')
			return (0);
		if (vars->args[i][*ii + 1])
		{
			if (vars->cmds[i].fd[0] != STDIN_FILENO)
				close(vars->cmds[i].fd[0]);
			vars->cmds[i].fd[0] = open(vars->args[i][*ii + 1], O_RDONLY, 0777);
			*ii += 1;
			if (vars->cmds[i].fd[0] == -1)
			{
				perror("Error");
				return (1);
			}
		}
		else
		{
			*ii += 1;
			printf("minishell: syntax error near unexpected token\n");
			return (1);
		}
	}
	return (0);
}

int	search_outfile_append(t_vars *vars, int i, int *ii)
{
	if (vars->args[i][*ii] && vars->args[i][*ii][0] == '>'
		&& vars->args[i][*ii + 1] && vars->args[i][*ii + 1][0] == '>')
	{	
		if (vars->args[i][*ii + 2] && vars->args[i][*ii + 2][0] != '<'
			&& vars->args[i][*ii + 2][0] != '>')
		{
			if (vars->cmds[i].fd[1] != STDOUT_FILENO)
				close (vars->cmds[i].fd[1]);
			vars->cmds[i].fd[1] = open(vars->args[i][*ii + 2], O_CREAT
					| O_APPEND | O_WRONLY, 0777);
			*ii += 2;
			if (vars->cmds[i].fd[1] < 0)
				return (1);
		}
		else
		{
			*ii += 2;
			printf("minishell: syntax error near unexpected token\n");
			return (1);
		}
	}
	return (0);
}

int	search_outfile(t_vars *vars, int i, int *ii)
{
	if (vars->args[i][*ii] && vars->args[i][*ii][0] == '>')
	{	
		if (vars->args[i][*ii + 1] && vars->args[i][*ii + 1][0] != '>' &&
			vars->args[i][*ii + 1][0] != '<')
		{
			if (vars->cmds[i].fd[1] != STDOUT_FILENO)
				close(vars->cmds[i].fd[1]);
			vars->cmds[i].fd[1] = open(vars->args[i][*ii + 1], O_CREAT | O_TRUNC
					| O_WRONLY, 0777);
			*ii += 1;
			if (vars->cmds[i].fd[1] < 0)
				return (1);
		}
		else
		{
			*ii += 1;
			printf("minishell: syntax error near unexpected token\n");
			return (1);
		}
	}
	return (0);
}

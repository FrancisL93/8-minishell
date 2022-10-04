/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:00:05 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/03 11:19:06 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//is < infile does not exist skip command
int	set_fds(t_vars *vars, int i)
{
	int	ii;

	ii = -1;
	vars->cmds[i].fd[0] = STDIN_FILENO;
	vars->cmds[i].fd[1] = STDOUT_FILENO;
	while (vars->args[i] && vars->args[i][++ii] != NULL)
	{
		if (search_heredoc(vars, i, &ii))
			return (1);
		if (search_infile(vars, i, ii))
			return (1);
		if (search_outfile(vars, i, &ii))
			return (1);
	}
	return (0);
}

int	put_fds(t_vars *vars, int i, int *ii, int out_type)
{
	if (out_type == 1)
	{
		vars->cmds[i].fd[1] = open(vars->args[i][*ii + 2], O_CREAT | O_APPEND
				| O_WRONLY, 0777);
		*ii += 1;
		if (vars->cmds[i].fd[1] == -1)
		{
			perror("Error: ");
			return (1);
		}
	}
	else if (out_type == 2)
	{
		vars->cmds[i].fd[1] = open(vars->args[i][*ii + 1], O_CREAT | O_TRUNC
				| O_WRONLY, 0777);
		if (vars->cmds[i].fd[1] == -1)
		{
			perror("Error: ");
			return (1);
		}
	}
	return (0);
}

int	set_input(t_vars *vars, int i)
{
	if (vars->cmds[i].fd[0] != STDIN_FILENO)
	{
		if (dup2(vars->cmds[i].fd[0], STDIN_FILENO) < 0)
		{
			perror("Couldn't dup2 standard input fd\n");
			close(vars->cmds[i].fd[0]);
			return (1);
		}
		close(vars->cmds[i].fd[0]);// à vérifier si cause problème
	}
	else if (i != 0)
	{
		if (dup2(vars->fd[(i - 1) * 2], STDIN_FILENO) < 0)
		{
			perror("Couldn't dup2 standard input fd\n");
			return (1);
		}
	}
	return (0);
}

int	set_output(t_vars *vars, int i)
{
	if (vars->cmds[i].fd[1] != STDOUT_FILENO)
	{
		if (dup2(vars->cmds[i].fd[1], STDOUT_FILENO) < 0)
		{
			perror("Couldn't dup2 standard input fd\n");
			close(vars->cmds[i].fd[1]);
			return (1);
		}
		close(vars->cmds[i].fd[1]); // à vérifier si cause problème
	}
	else if (i < vars->pipe - 1)
	{
		if (dup2(vars->fd[i * 2 + 1], STDOUT_FILENO) < 0)
		{
			perror("Couldn't dup2 standard output fd\n");
			return (1);
		}
	}
	return (0);
}

int	create_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe)
	{
		if (pipe(vars->fd + i * 2) == -1)
		{
			perror("Error: ");
			while (i >= 0)
			{
				close(vars->fd[i * 2]);
				close(vars->fd[i * 2 + 1]);
				i--;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

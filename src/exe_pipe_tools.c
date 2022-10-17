/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:00:05 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/17 11:09:55 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Set default fds and loop into redirections
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
		if (search_infile(vars, i, &ii))
			return (1);
		if (search_outfile_append(vars, i, &ii))
			return (1);
		if (search_outfile(vars, i, &ii))
			return (1);
	}
	return (0);
}

//dup2 redirection or pipe fd
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
		close(vars->cmds[i].fd[0]);
	}
	else if (i != 0)
	{
		if (dup2(vars->fd[(i - 1) * 2], STDIN_FILENO) < 0)
		{
			perror("Couldn't dup2 standard input fd\n");
			return (1);
		}
		close(vars->fd[(i - 1) * 2]);
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
		close(vars->cmds[i].fd[1]);
	}
	else if (i < vars->pipe - 1)
	{
		if (dup2(vars->fd[i * 2 + 1], STDOUT_FILENO) < 0)
		{
			perror("Couldn't dup2 standard output fd\n");
			return (1);
		}
		close(vars->fd[i * 2 + 1]);
	}
	return (0);
}

//Create number of pipes necessary to execute pipe commands
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
				close (vars->fd[i * 2]);
				close(vars->fd[i * 2 + 1]);
				i--;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

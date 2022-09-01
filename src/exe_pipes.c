/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:06:47 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/01 09:53:15 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_pipes(t_vars *vars, char *input)
{
	pid_t	*pid;
	int		**pipefd;
	int		i;

	i = 0;
	pipefd = malloc(sizeof(int**) * (vars->pipe + 1));
	pid = malloc(sizeof(*pid) * (vars->pipe + 1));
	pipefd[i] = malloc(sizeof(int*) * 2);
	while (i < vars->pipe)
	{
		pipefd[i] = malloc(sizeof(int*) * 2);
		pipe(pipefd[i]);
		pid[i] = fork();
	}
	i = 0;
	while (i < vars->pipe)
	{
		if (pid[i])
		{
			close(pipefd[i][1]);
			dup2(pipefd[i][0], STDIN_FILENO);
		}
		else
		{
			close(pipefd[i][0]);
			dup2(pipefd[i][1], STDOUT_FILENO);
			if (vars->fdin == STDIN_FILENO)
				exit(1);
			else
				execute_cmd(input);
		}
	}
}
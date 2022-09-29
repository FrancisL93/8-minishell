/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:32:57 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/27 14:33:31 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/minishell.h"

//if heredoc use heredoc fonctions and print in right fd, no need to open.
void	ft_is_redirector(t_vars *vars, int i)
{
	int	ii;

	ii = -1;
	while (vars->args[i][++ii] != NULL)
	{
		if (vars->args[i][ii][0] == '<' && vars->args[i][ii + 1][0] == '<')
		{
			vars->fd[i * 2 + 1] = open(vars->args[i][ii + 2], O_CREAT | O_APPEND
					| O_WRONLY, 0777);
			if (dup2(vars->fd[i * 2 + 1], STDOUT_FILENO) < 0)
			{
				perror("Couldn't dup2 standard output fd\n");
				return ;
			}
			if (i != 0)
			{
				if (dup2(vars->fd[(i - 1) * 2], STDIN_FILENO) < 0)
				{
					perror("Couldn't dup2 standard input fd\n");
					return ;
				}
			}
			check_heredoc(vars, i);
		}
		else if (vars->args[i][ii][0] == '<' && vars->args[i][ii][1] == '\0')
		{
			vars->fd[(i - 1) * 2] = open(vars->args[i][ii + 1], O_RDONLY, 0777);
			if (dup2(vars->fd[(i - 1) * 2], STDIN_FILENO) < 0)
			{
				perror("Couldn't dup2 standard input fd\n");
				return ;
			}
			if (i < vars->pipe - 1)
			{
				if (dup2(vars->fd[i * 2 + 1], STDOUT_FILENO) < 0)
				{
					perror("Couldn't dup2 standard output fd\n");
					return ;
				}
			}
			return ;
		}
		else if (vars->args[i][ii][0] == '>' && vars->args[i][ii][1] == '\0')
		{
			vars->fd[i * 2 + 1] = open(vars->args[i][ii + 1], O_CREAT | O_TRUNC
					| O_WRONLY, 0777);
			if (dup2(vars->fd[i * 2 + 1], STDOUT_FILENO) < 0)
			{
				perror("Couldn't dup2 standard output fd\n");
				return ;
			}
			if (i != 0)
			{
				if (dup2(vars->fd[(i - 1) * 2], STDIN_FILENO) < 0)
				{
					perror("Couldn't dup2 standard input fd\n");
					return ;
				}
			}
			return ;
		}
	}
	if (i != 0)
	{
		if (dup2(vars->fd[(i - 1) * 2], STDIN_FILENO) < 0)
		{
			perror("Couldn't dup2 standard input fd\n");
			return ;
		}
	}
	if (i < vars->pipe - 1)
	{
		if (dup2(vars->fd[i * 2 + 1], STDOUT_FILENO) < 0)
		{
			perror("Couldn't dup2 standard output fd\n");
			return ;
		}
	}
}

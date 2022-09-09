/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:26:17 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/09 14:53:58 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    ft_is_redirector(t_vars *vars, int i, int ii)
{
    vars->fdin = 0;
    vars->fdout = 1;
    while (vars->cmds[i][ii] != NULL)
    {
        if (vars->cmds[i][ii][0] == '<' && vars->cmds[i][ii][1] == '\0')
        {
            vars->inf = ft_strdup(vars->cmds[i][ii + 1]);
            //free_redir(vars, i, ii);
            vars->fdin = open(vars->inf, O_RDONLY, 0777);
            return ;
        }
        else if (vars->cmds[i][ii][0] == '>' && vars->cmds[i][ii][1] == '\0')
        {
            vars->outf = ft_strdup(vars->cmds[i][ii + 1]);
            //free_redir(vars, i, ii);
            vars->fdout = open(vars->outf, O_CREAT | O_TRUNC | O_WRONLY, 0777);
            return ;
        }
        else if (vars->cmds[i][ii][0] == '>' && vars->cmds[i][ii][1] == '>')
        {
            vars->outappf = ft_strdup(vars->cmds[i][ii + 1]);
            //free_redir(vars, i, ii);
            vars->fdout = open(vars->outappf, O_CREAT | O_APPEND
                    | O_WRONLY, 0777);
            return ;
        }
        ii ++;
    }
}

void	execute_cmd(t_vars *vars, int i)
{
	char	*cmd;
	int 	ii;

	ii = 0;
	while (vars->cmds[i][ii] != NULL && access(cmd, F_OK | X_OK) != 0)
    {
        if (ft_strichr(vars->cmds[i][ii], '/') > -1)
            cmd = vars->cmds[i][ii];
        else
            cmd = get_path(vars->cmds[i][ii], vars->env);
        ii++;
    }
	//if (!vars->cmds[i] || !vars->cmds[i][0])
	 //	exit(127);
	//if (ft_strichr(vars->cmds[i][0], '/') > -1)
	//	cmd = vars->cmds[i][0];
	//else
		cmd = get_path(vars->cmds[i][0], vars->env);
	execve(cmd, vars->cmds[i], vars->env);
	ft_putstr_fd("Error: Command not found (", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	exit(127);
}

void	execute(t_vars *vars)
{
	int	i;
	int	j;
	int **fd;
	int *pid;
	int status;

	i = -1;
	vars->cmds = split_cmds(vars);
	pid = malloc(sizeof(int) * vars->pipe);
	fd = malloc(sizeof(int *) * vars->pipe);
	while (++i < vars->pipe)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (pipe(fd[i]))
			return ;
		pid[i] = fork();
		if (pid[i] < 0)
			return ;
		if (pid[i] == 0)
		{	
			j = -1;
			while (++j < i)
			{
				close(fd[j][0]);
				close(fd[j][1]);
			}
			close(fd[i][0]);
			execute_cmd(vars, i);
		}
	}
	i = -1;
	while (++i < vars->pipe)
	{
		close(fd[i][1]);
		close(fd[i][0]);
	}
	while (i > 0)
		waitpid(pid[--i], &status, 0);
}

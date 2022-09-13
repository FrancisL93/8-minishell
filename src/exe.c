/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exe.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: anhebert <anhebert@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/09/09 11:26:17 by flahoud		   #+#	#+#			 */
/*   Updated: 2022/09/09 15:32:39 by anhebert		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_is_redirector(t_vars *vars, int i)
{
	int	ii;

	ii = 0;
	vars->cmds[i].fdin = 0;
	vars->cmds[i].fdout = 1;
	while (vars->args[i][ii] != NULL)
	{
		if (vars->args[i][ii][0] == '<' && vars->args[i][ii][1] == '\0')
		{
			vars->cmds[i].inf = ft_strdup(vars->args[i][ii + 1]);
			vars->cmds[i].fdin = open(vars->cmds[i].inf, O_RDONLY, 0777);
			return ;
		}
		else if (vars->args[i][ii][0] == '>' && vars->args[i][ii][1] == '\0')
		{
			vars->cmds[i].outf = ft_strdup(vars->args[i][ii + 1]);
			vars->cmds[i].fdout = open(vars->cmds[i].outf, O_CREAT | O_TRUNC | O_WRONLY, 0777);
			return ;
		}
		else if (vars->args[i][ii][0] == '>' && vars->args[i][ii][1] == '>')
		{
			vars->cmds[i].outfapp = ft_strdup(vars->args[i][ii + 1]);
			vars->cmds[i].fdout = open(vars->cmds[i].outfapp, O_CREAT | O_APPEND
					| O_WRONLY, 0777);
			return ;
		}
		ii ++;
	}
}
/* 
void	execute_cmd(t_vars *vars, int i)
{
	if (!vars->cmds || !vars->cmds[i].cmds[0])
		exit(127);
	if (ft_strichr(vars->cmds[i].cmds[0], '/') > -1)
		vars->cmds[i].cmd = vars->cmds[i].cmds[0];
	else
		vars->cmds[i].cmd = get_path(vars->cmds[i].cmds[0], vars->env);
	// créer un ** pour avoir seulement les éléments de la commande //
	execve(vars->cmds[i].cmd, vars->cmds[i].cmds, vars->env);
	ft_putstr_fd("Error: Command not found (", STDERR_FILENO);
	ft_putstr_fd(vars->cmds[i].cmd, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	exit(127);
}

void	execute(t_vars *vars)
{
	int	i;
	int	j;
	int	**fd;
	int	*pid;
	int	status;

	i = -1;
	split_cmds(vars);
	pid = malloc(sizeof(int) * vars->pipe);
	fd = malloc(sizeof(int *) * vars->pipe);
	while (++i < vars->pipe)
	{
		//ft_is_redirector(vars, i, 0);
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
			dup2(fd[i][0], 0);
			dup2(vars->cmds[i].fdout, 1);
			close(fd[i][1]);
			execute_cmd(vars, i);
			close(vars->cmds[i].fdout);
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
} */

void	child_process(t_vars *vars, int i)
{
	int		ret;

	ret = 0;
	if (!vars->cmds || !vars->cmds[i].cmds[0])
		exit(127);
	if (ft_strichr(vars->cmds[i].cmds[0], '/') > -1)
		vars->cmds[i].cmd = vars->cmds[i].cmds[0];
	else
		vars->cmds[i].cmd = get_path(vars->cmds[i].cmds[0], vars->env);
	if (dup2(vars->cmds[i].fdin, STDOUT_FILENO) < 0)
		return ;
	if (dup2(vars->cmds[i].fdout, STDIN_FILENO) < 0)
		return ;
	ret = execve(vars->cmds[i].cmd, vars->cmds[i].cmds, vars->env);
	ft_putstr_fd("Error: Command not found (", STDERR_FILENO);
	ft_putstr_fd(vars->cmds[i].cmd, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	exit(ret);
}

void	execute_command(t_vars *vars, int i)
{
	vars->cmds[i].pid = fork();
	if (vars->cmds[i].pid < 0)
		return ;
	else if (vars->cmds[i].pid == 0)
		child_process(vars, i);
	else
	{
		if (vars->pipe > 1)
		{
			close(vars->cmds[i].fdin);
			if (vars->cmds[i + 1].index == vars->pipe)
				close(vars->cmds[i].fdout);
		}
		if (vars->cmds[i].index != 0)
			close(vars->cmds[i - 1].fdout);
	}
}

void	execute(t_vars *vars)
{
	int	status;
	int	i;

	i = 0;
	split_cmds(vars);
	while (i < vars->pipe)
	{
		ft_is_redirector(vars, i);
		printf("%d vs 0\n", vars->cmds->fdin);
		printf("%d vs 1\n", vars->cmds->fdout);
		execute_command(vars, i);
		i++;
	}
	i = 0;
	while (i < vars->pipe)
	{
		waitpid(vars->cmds[i].pid, &status, 0);
		i++;
	}
}


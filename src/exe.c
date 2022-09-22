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

//if heredoc use heredoc fonctions and print in right fd, no need to open.
void	ft_is_redirector(t_vars *vars, int i)
{
	int	ii;

	ii = -1;
	while (vars->args[i][++ii] != NULL)
	{
		if (vars->args[i][ii][0] == '<' && vars->args[i][ii + 1][0] == '<')
		{
			// vars->fd[i * 2 + 1] = open(vars->args[i][ii + 2], O_CREAT | O_APPEND
			// 		| O_WRONLY, 0777);
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

int	check_export(t_vars *vars, int i)
{
	if (!ft_strncmp(vars->cmds[i].cmds[0], "export", 6))
		export(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

int	check_cd(t_vars *vars, int i)
{
	if (!ft_strncmp(vars->cmds[i].cmds[0], "cd", 2))
		cd(vars, vars->cmds[i].cmds[1]);
	else
		return (0);
	return (1);
}

int	check_var(t_vars *vars, int i)
{
	int		j;
	int		res;

	j = -1;
	if (i != vars->pipe - 1)
		return (1);
	while (vars->cmds[i].cmds[++j])
	{
		res = add_variable(vars, vars->cmds[i].cmds[j]);
		if (res == 1)
			return (1);
	}
	return (0);
}

int	check_built_in(t_vars *vars, int i)
{
	if (!ft_strncmp(vars->cmds[i].cmds[0], "echo", 4))
		echo(vars, i);
	else if (!ft_strncmp(vars->cmds[i].cmds[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(vars->cmds[i].cmds[0], "export", 6))
		return (1);
	else if (!ft_strncmp(vars->cmds[i].cmds[0], "pwd", 3))
		print_path();
	else if (!ft_strncmp(vars->cmds[i].cmds[0], "env", 3))
		print_env(vars);
	else
		return (0);
	return (1);
}

// check built in, si derniere commande et contient =, ajouter la ou les variables à la linkedlist ,
void	child_process(t_vars *vars, int i)
{
	int		ret;
	int		j;

	j = -1;
	ret = 0;
	while (++j < (vars->pipe - 1) * 2)
		close(vars->fd[j]);
	ft_is_redirector(vars, i);
	if (!vars->cmds || !vars->cmds[i].cmds[0])
		exit(127);
	ret = check_built_in(vars, i);
	if (ret)
		exit(ret);
	if (ft_strichr(vars->cmds[i].cmds[0], '/') > -1)
		vars->cmds[i].cmd = vars->cmds[i].cmds[0];
	else
		vars->cmds[i].cmd = get_path(vars->cmds[i].cmds[0], vars->env);
	ret = execve(vars->cmds[i].cmd, vars->cmds[i].cmds, vars->env);
	ft_putstr_fd("Error: Command not found (", STDERR_FILENO);
	ft_putstr_fd(vars->cmds[i].cmd, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	exit(0);
}

void	execute_command(t_vars *vars, int i)
{
	vars->cmds[i].pid = fork();
	if (vars->cmds[i].pid < 0)
		return ;
	if (vars->cmds[i].pid == 0)
	{
		init_signals(1);
		// if (i != 0)
		// {
		// 	if (dup2(vars->fd[(i - 1) * 2], STDIN_FILENO) < 0)
		// 	{
		// 		perror("Couldn't dup2 standard input fd\n");
		// 		return ;
		// 	}
		// }
		// if (i < vars->pipe - 1)
		// {
		// 	if (dup2(vars->fd[i * 2 + 1], STDOUT_FILENO) < 0)
		// 	{
		// 		perror("Couldn't dup2 standard output fd\n");
		// 		return ;
		// 	}
		// }
		child_process(vars, i);
	}
		init_signals(2);
}

void	execute(t_vars *vars)
{
	int	status;
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	vars->fd = malloc(sizeof(int) * (vars->pipe -1) * 2);
	split_cmds(vars);
	while (++i < vars->pipe - 1)
		if (pipe(vars->fd + i * 2) == -1)
			return ;
	i = -1;
	while (++i < vars->pipe)
	{
		if (!vars->cmds[i]. cmds[0])
			break ;
		if (ft_strichr(vars->cmds[i].cmds[0], '=') > 0)
			ret = check_var(vars, i);
		if (ret != 1 && vars->pipe == 1)
			ret = check_export(vars, i);
		if (ret != 1 && vars->pipe == 1)
			ret = check_cd(vars, i);
		if (ret != 1)
			execute_command(vars, i);
	}
	i = -1;
	while (++i < (vars->pipe - 1) * 2)
		close(vars->fd[i]);
	i = -1;
	i = -1;
	while (++i < vars->pipe)
		waitpid(vars->cmds[i].pid, &status, 0);
	free(vars->fd);
	//vars->exit_status = status; ou créer une variable $? 
	init_signals(0);
}

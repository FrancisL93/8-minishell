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

void	child_process(t_vars *vars, int i)
{
	int		ret;
	int		j;

	j = -1;
	ret = 0;
	vars->exit_stat = 0;
	while (++j < (vars->pipe - 1) * 2)
		close(vars->fd[j]);
	if (!vars->cmds || !vars->cmds[i].cmds[0])
		exit(127);
	ret = check_built_in(vars, i);
	if (ret)
		exit(vars->exit_stat);
	if (ft_strichr(vars->cmds[i].cmds[0], '/') > -1)
		vars->cmds[i].cmd = vars->cmds[i].cmds[0];
	else
		vars->cmds[i].cmd = get_path(vars->cmds[i].cmds[0], vars->env);
	ret = execve(vars->cmds[i].cmd, vars->cmds[i].cmds, vars->env);
	if (ret == -1)
		perror("Error");
	exit(errno);
}

void	execute_command(t_vars *vars, int i)
{
	vars->cmds[i].pid = fork();
	if (vars->cmds[i].pid < 0)
		return ;
	if (vars->cmds[i].pid == 0)
	{
		init_signals(1);
		if (set_input(vars, i))
			exit (1);
		if (set_output(vars, i))
			exit (1);
		child_process(vars, i);
	}
	init_signals(2);
}

int	check_command(t_vars *vars)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < vars->pipe)
	{
		if (!vars->cmds[i].cmds[0] && vars->args[i][0])
			ret = 1;
		if (ret != 1 && ft_strichr(vars->cmds[i].cmds[0], '=') > 0)
			ret = check_var(vars, i);
		if (ret != 1 && vars->pipe == 1)
			ret = check_unset(vars, i);
		if (ret != 1 && vars->pipe == 1)
			ret = check_export(vars, i);
		if (ret != 1 && vars->pipe == 1)
			ret = check_cd(vars, i);
		ret = set_fds(vars, i);
		if (ret != 1)
			execute_command(vars, i);
		i++;
	}
	return (ret);
}

void	close_fds(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < (vars->pipe * 2))
	{
		close(vars->fd[i]);
		i++;
	}
	free(vars->fd);
}

void	execute(t_vars *vars)
{
	int		i;

	i = -1;
	if (!vars->token.tokens)
		return ;
	vars->fd = malloc(sizeof(int) * vars->pipe * 2);
	if (!vars->fd)
		return ;
	split_cmds(vars);
	if (create_pipes(vars) || check_command(vars))
	{
		close_fds(vars);
		return ;
	}
	close_fds(vars);
	while (++i < vars->pipe)
	{
		waitpid(vars->cmds[i].pid, &vars->exit_stat, 0);
		if (WIFEXITED(vars->exit_stat))
			add_exit(vars, WEXITSTATUS(vars->exit_stat));
	}
	init_signals(0);
}

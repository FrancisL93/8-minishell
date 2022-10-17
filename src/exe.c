/* ************************************************************************** */
/*																		  	  */
/*														:::	  ::::::::        */
/*   exe.c											  :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: anhebert <anhebert@student.42.fr>		  +#+  +:+	   +#+		      */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2022/09/09 11:26:17 by flahoud		   #+#	#+#		          */
/*   Updated: 2022/09/09 15:32:39 by anhebert		 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_fds(t_vars *vars, int parent)
{
	int		i;

	i = 0;
	while (i < (vars->pipe))
	{
		if (vars->fd)
		{
			close(vars->fd[i * 2]);
			close(vars->fd[i * 2 + 1]);
		}
		if (vars->cmds[i].fd[0] != STDIN_FILENO)
			close(vars->cmds[i].fd[0]);
		if (vars->cmds[i].fd[1] != STDOUT_FILENO)
			close(vars->cmds[i].fd[1]);
		i++;
	}
	if (vars->fd && parent)
		free(vars->fd);
}

//Close all fds
//Execute built-in if it is -> search path of command if no "/"
//Execute command and save exit status into $?
//close remaining fds if command fails
void	child_process(t_vars *vars, int i)
{
	int		ret;
	int		j;
	char	*path;

	j = -1;
	ret = 0;
	path = NULL;
	vars->exit_stat = 0;
	close_fds(vars, 0);
	if (!vars->cmds || !vars->cmds[i].cmds[0] || !vars->cmds[i].cmds[0][0])
		quit_terminal(vars, 127);
	ret = check_built_in(vars, i, 0);
	if (ret)
		quit_terminal(vars, 0);
	if (ft_strichr(vars->cmds[i].cmds[0], '/') > -1)
		vars->cmds[i].cmd = ft_strdup(vars->cmds[i].cmds[0]);
	else
		vars->cmds[i].cmd = get_path(path, vars->cmds[i].cmds[0], vars->env);
	ret = execve(vars->cmds[i].cmd, vars->cmds[i].cmds, vars->env);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(vars->cmds[i].cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	close_fds(vars, 1);
	quit_terminal(vars, 127);
}

//fork into a new process to exec command
//dup2 redirections or stdin/stdout depending on needs
//set new signals on parent to execute children signals only
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

//Check if built-in or error in input in a loop for each pipe
int	check_command(t_vars *vars)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < vars->pipe)
	{
		if (!vars->cmds[i].cmds[0] && !vars->args[i][0])
		{
			printf("syntax error near unexpected token `|'\n");
			return (1);
		}
		if (!vars->cmds[i].cmds[0] && vars->args[i][0])
			ret = 2;
		else
			ret = check_built_in(vars, i, 1);
		if (ret < 1 && ft_strichr(vars->cmds[i].cmds[0], '=') > 0)
			ret = check_var(vars, i);
		if (ret != 1)
			ret = set_fds(vars, i);
		if (ret != 1)
			execute_command(vars, i);
		i++;
	}
	return (ret);
}

//Parent wait for child exit status and reset signals to normal handling
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
		close_fds(vars, 1);
		return ;
	}
	close_fds(vars, 1);
	while (++i < vars->pipe)
	{
		waitpid(vars->cmds[i].pid, &vars->exit_stat, 0);
		if (WIFEXITED(vars->exit_stat))
			add_exit(vars, WEXITSTATUS(vars->exit_stat));
	}
	init_signals(0);
}

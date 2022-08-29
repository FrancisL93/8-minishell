/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:17:40 by flahoud           #+#    #+#             */
/*   Updated: 2022/08/29 16:46:48 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_built_in(t_vars *vars, char *input)
{
	if (!ft_strncmp(tolower_str(vars->cmd), "env", 3))
		print_env();
	if (!ft_strncmp(tolower_str(vars->cmd), "pwd", 3))
		print_path();
	if (!ft_strncmp(tolower_str(vars->cmd), "echo", 5))
		echo(input);
	if (!ft_strncmp(tolower_str(vars->cmd), "cd", 2))
		cd(input);
	if (!ft_strncmp(tolower_str(vars->cmd), "export", 6))
		export(input);
}

//remplacer ft_split par lexer
void	execute_cmd(char *input)
{
	char	**cmdstr;
	char	*cmd;

	cmdstr = ft_split(input, ' ');
	if (cmdstr[0] == NULL)
		exit(127);
	if (ft_strichr(cmdstr[0], '/') > -1)
		cmd = cmdstr[0];
	else
		cmd = get_path(cmdstr[0], environ);
	execve(cmd, cmdstr, environ);
	ft_putstr_fd("Error: Command not found (", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	exit(127);
}

int	execute(t_vars *vars, char *input)
{
	pid_t	pid;

	if (vars->built_in)
		execute_built_in(vars, input);
	else
	{
		pid = fork();
		if (pid == 0)
			execute_cmd(input);
		else if (pid != 0)
			wait(&pid);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:17:40 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/01 11:19:47 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_built_in(t_vars *vars, char *input)
{
	if (!ft_strncmp(tolower_str(vars->cmd), "env", 3))
		print_env();
	if (!ft_strncmp(tolower_str(vars->cmd), "pwd", 3))
		print_path();
	if (!ft_strncmp(tolower_str(vars->cmd), "echo", 4))
		echo(vars);
	if (!ft_strncmp(tolower_str(vars->cmd), "cd", 2))
		cd(input);
	if (!ft_strncmp(tolower_str(vars->cmd), "export", 6))
		export(vars, input);
}

//remplacer ft_split par lexer
/* void	execute_cmd(char *input)
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
} */

void	execute_cmd(t_vars *vars)
{
	char	*cmd;

	if (vars->token.tokens[0] == NULL)
		exit(127);
	if (ft_strichr(vars->token.tokens[0], '/') > -1)
		cmd = vars->token.tokens[0];
	else
		cmd = get_path(vars->token.tokens[0], environ);
	execve(cmd, vars->token.tokens, environ);
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
	else if (vars->pipe > 0)
		execute_pipes(vars, input);
	else
	{
		pid = fork();
		if (pid == 0 && !vars->pipe)
			execute_cmd(vars);
		else if (pid != 0)
			wait(&pid);
	}
	return (0);
}

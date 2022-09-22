/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:58:38 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/08 13:58:42 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*subsubsplit(t_vars *vars, int *j)
{
	char	*cmd;
	int		i;
	int		len;

	i = 0;
	if (!vars->token.tokens[*j])
		return (NULL);
	len = ft_strlen(vars->token.tokens[*j]);
	cmd = ft_calloc(sizeof(char), len + 1);
	if (*j > vars->nb_tokens)
		return (NULL);
	if (!ft_strncmp(vars->token.tokens[*j], "|", 1))
		return (NULL);
	while (vars->token.tokens[*j][i])
	{
		cmd[i] = vars->token.tokens[*j][i];
		i++;
	}
	return (cmd);
}

char	**subsplit(t_vars *vars, int *j)
{
	int		i;
	char	**cmds;

	i = 0;
	cmds = ft_calloc(sizeof(char *), vars->nb_tokens + 1);
	while (1)
	{
		cmds[i] = subsubsplit(vars, j);
		if (cmds[i] == NULL)
		{
			*j += 1;
			break ;
		}
		else
		{
			*j += 1;
			i++;
		}
	}
	return (cmds);
}

char	***split_cmds(t_vars *vars, int nb_pipes)
{
	int		i;
	int		ii;
	int		j;
	char	***cmds;

	i = 0;
	ii = 0;
	j = 0;
	cmds = ft_calloc(sizeof(char **), nb_pipes + 1);
	while (i <= nb_pipes)
	{
		cmds[i] = subsplit(vars, &j);
		i++;
	}
	return (cmds);
}

void	execute_cmd_pipes(t_vars *vars)
{
	char	*cmd;

	if (vars->token.tokens[0] == NULL)
		exit(127);
	if (ft_strichr(vars->token.tokens[0], '/') > -1)
		cmd = vars->token.tokens[0];
	else
		cmd = get_path(vars->token.tokens[0], vars->env);
	execve(cmd, vars->token.tokens, vars->env);
	ft_putstr_fd("Error: Command not found (", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	exit(127);
}

// Envoyer les commandes dans le pipe avec la nouvelle variable cmds //
void	execute_pipes(t_vars *vars)
{
	pid_t	*pid;
	int		**pipefd;
	int		i;
	int		nb_pipes;
	char	***cmds;

	i = 0;
	nb_pipes = vars->pipe;
	pipefd = malloc(sizeof(int**) * (vars->pipe + 1));
	pid = malloc(sizeof(*pid) * (vars->pipe + 1));
	pipefd[i] = malloc(sizeof(int*) * 2);
	cmds = split_cmds(vars, nb_pipes);
	 while (i < vars->pipe)
	{
		pipefd[i] = malloc(sizeof(int*) * 2);
		pipe(pipefd[i]);
		pid[i] = fork();
		i++;
	}
	i = 0;
	while (i < vars->pipe)
	{
		if (pid[i])
		{
			close(pipefd[i][1]);
			dup2(pipefd[i][0], STDIN_FILENO);
			execute_cmd_pipes(vars);
		}
		else
		{
			close(pipefd[i][0]);
			dup2(pipefd[i][1], STDOUT_FILENO);
			if (vars->fdin == STDIN_FILENO)
				exit(1);
			//else
		}
		i++;
	} 
}
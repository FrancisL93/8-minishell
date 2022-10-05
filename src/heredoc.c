/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:22:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/05 16:22:47 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	start_heredoc(char *eof)
{
	char	*input;
	int		fd[2];

	input = readline(">");
	if (pipe(fd) < 0)
		return (-1);
	while (input && ft_strcmp(input, eof))
	{
		ft_putstr_fd(input, fd[1]);
		write(fd[1], "\n", 1);
		free(input);
		input = readline(">");
	}
	close (fd[1]);
	free(input);
	return (fd[0]);
}

int	search_heredoc(t_vars *vars, int i, int *ii)
{
	if (vars->args[i][*ii][0] == '<' && vars->args[i][*ii + 1] \
		&& vars->args[i][*ii + 1][0] == '<')
	{
		if (vars->args[i][*ii + 2] && vars->args[i][*ii + 2][0] != '<'
			&& vars->args[i][*ii + 2][0] != '>')
		{
			vars->cmds[i].fd[0] = start_heredoc(vars->args[i][*ii + 2]);
			if (vars->cmds[i].fd[0] < 0)
				return (1);
			*ii += 2;
		}
		else
		{
			*ii += 2;
			printf("minishell: syntax error near unexpected token\n");
			return (1);
		}
	}
	return (0);
}

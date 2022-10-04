/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:22:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/03 11:35:42 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	start_heredoc(char *eof, int fd)
{
	char	*input;

	input = readline(">");
	while (ft_strcmp(input, eof))
	{
		ft_putstr_fd(input, fd);
		write(fd, "\n", 1);
		free(input);
		input = readline(">");
	}
	free(input);
}

int	search_heredoc(t_vars *vars, int i, int *ii)
{
	if (vars->args[i][*ii][0] == '<' && vars->args[i][*ii + 1] \
		&& vars->args[i][*ii + 1][0] == '<')
	{
		if (vars->args[i][*ii + 2])
		{
			vars->cmds[i].fd[1] = open("minishell_tmp_v2022", O_CREAT | O_TRUNC
					| O_RDWR, 0777);
			if (vars->cmds[i].fd[1] == -1)
			{
				perror("Error bitch: ");
				return (1);
			}
			start_heredoc(vars->args[i][*ii + 2], vars->cmds[i].fd[1]);
			*ii += 1;
		}
	}
	return (0);
}

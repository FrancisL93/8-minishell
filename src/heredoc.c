/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:22:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/17 10:22:54 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	write_var(t_vars *vars, char *str, int *fd, int i)
{
	int		j;
	char	*dup;
	char	*var;

	j = 0;
	while (str[i + j] && (str[i + j] != ' ' || str[i + j] != '$'))
		j++;
	dup = ft_strndup(&str[i], j);
	var = get_variable(vars, dup);
	free(dup);
	j = 0;
	while (var && var[j])
		write(fd[1], &var[j++], 1);
}

void	write_heredoc(t_vars *vars, char *str, int *fd)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			write_var(vars, str, fd, i);
			while (str[i] && str[i + 1] && str[i + 1] != ' '
				&& str[i + 1] != '$')
				i++;
		}
		else
			write(fd[1], &str[i], 1);
		i++;
	}
	write(fd[1], "\n", 1);
}

//Start a readline until eof into a new pipe
int	start_heredoc(t_vars *vars, char *eof)
{
	char	*input;
	int		fd[2];

	input = readline(">");
	if (pipe(fd) < 0)
		return (-1);
	while (input && ft_strcmp(input, eof))
	{
		write_heredoc(vars, input, fd);
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
			if (vars->cmds[i].fd[0] != STDIN_FILENO)
				close(vars->cmds[i].fd[0]);
			vars->cmds[i].fd[0] = start_heredoc(vars, vars->args[i][*ii + 2]);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:06:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/08/31 14:32:06 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_variable(char *input)
{
	char	*var;
	int		i;

	i = 0;
	while (input[++i] != ' ')
		i++;
	while (input[++i] == ' ')
		i++;
	var = &input[i];
	return (var);
}

char	*find_variable(t_vars *vars, char *input)
{
	char	*heredoc_var;
	char	*var;
	
	var = get_variable(input);
	heredoc_var = get_next_line(vars->heredoc_fd);
	while (heredoc_var)
	{
		printf("%s\n", heredoc_var);
		if (!ft_strncmp(heredoc_var, var, ft_strlen(var)))
			return (heredoc_var);
		free(heredoc_var);
		heredoc_var = get_next_line(vars->heredoc_fd);
	}
	return (NULL);
}

void	add_variable(t_vars *vars, char *input)
{
	ft_putstr_fd(get_variable(input), vars->heredoc_fd);
	ft_putstr_fd("\n", vars->heredoc_fd);
}

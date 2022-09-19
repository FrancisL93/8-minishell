/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:22:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/19 08:36:29 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// char	*set_here_prompt(int n_pipe)
// {
// 	char	*prompt;
// 	char	pipe[5] = "pipe ";
// 	char	heredoc[9] = "heredoc> ";
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = -1;
// 	prompt = malloc(sizeof(char) * (9 + (n_pipe - 1) + 1));
// 	while (++i < (n_pipe - 1) * 5)
// 		prompt[++j] = pipe[i % 5];
// 	while (++j < (n_pipe - 1) * 5 + 9)
// 		prompt[j] = heredoc[(j - i) % 9];
// 	return (prompt);
// }

// void	start_heredoc(t_vars *vars, char *stopper, int i)
// {
// 	t_list	*heredoc;
// 	t_list	*result;
// 	char	*line;
// 	char	*here_prompt;

// 	here_prompt = set_here_prompt(vars->pipe);
// 	heredoc = NULL;
// 	result = heredoc;
// 	line = readline(here_prompt);
// 	while (ft_strncmp(line, stopper, ft_strlen(stopper)))
// 	{
// 		heredoc->content = line;
// 		heredoc = heredoc->next;
// 		if (line && line[0])
// 			free(line);
// 		line = readline(here_prompt);
// 	}
// 	free(here_prompt);
// 	while (result)
// 	{
// 		ft_putstr_fd(result->content, vars->fd[i * 2 + 1]);
// 		write (vars->fd[i * 2 + 1], "\n", 1);
// 		result = result->next;
// 	}
// 	exit(0);
// }

// void	check_heredoc(t_vars *vars, int i)
// {
// 	int		j;
// 	char	*stopper;

// 	j = 0;
// 	while (vars->cmds[i].cmds[j] && ft_strncmp(vars->cmds[i].cmds[j], "<<", 2))
// 		j++;
// 	if (vars->cmds[i].cmds[j++] == NULL)
// 		return ;
// 	if (vars->cmds[i].cmds[j])
// 		stopper = vars->cmds[i].cmds[j];
// 	else
// 		return ;
// 	if (ft_strlen(stopper) < 1)
// 		return ;
// 	else
// 		start_heredoc(vars, stopper, i);
// }


//tmp files ?

void	check_heredoc(t_vars *vars, int i)
{
	int		j;
	char	*stopper;

	j = 0;
	while (vars->cmds[i].cmds[j] && ft_strncmp(vars->cmds[i].cmds[j], "<<", 2))
		j++;
	if (vars->cmds[i].cmds[j++] == NULL)
		return ;
	if (vars->cmds[i].cmds[j])
		stopper = vars->cmds[i].cmds[j];
}

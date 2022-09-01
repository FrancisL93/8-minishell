/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:06:35 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/01 12:36:46 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



void	heredoc(t_vars *vars)
{
	char	*input;
	char	*herestr;
	t_list	**here;
	
	here = NULL;	
	rl_on_new_line();
	input = readline("heredoc> ");
	while (ft_strncmp(input, vars->heredoc_eof, (ft_strlen(input))))
	{
		ft_lstadd_back(here, ft_lstnew(&input));
		herestr = ft_strdup(herestr);
		free(input);
		rl_on_new_line();
		input = readline("heredoc> ");
	}
}
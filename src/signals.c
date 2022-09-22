/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:41:43 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/22 09:50:11 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_handler_children(int sig)
{
	if (sig == SIGQUIT)
		(void) SIGQUIT;
	if (sig == SIGINT)
		(void) SIGINT;
}

void	sig_handler_parent(int sig)
{
	if (sig == SIGQUIT)
		printf("\n");
	else if (sig == SIGINT)
		printf("\n");
}

void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(int children)
{
	struct sigaction	sa;

	if (children == 2)
		sa.sa_handler = &sig_handler_parent;
	else if (children == 1)
		sa.sa_handler = &sig_handler_children;
	else
		sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

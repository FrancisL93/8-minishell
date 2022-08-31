/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:09:26 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/31 14:23:59 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	build_lexer(t_vars *vars, char *input)
{
	if (vars || input)
		return ;
}

void	check_built_in(t_vars *vars, char *cmd)
{
	char	**built_in;
	int		i;

	i = -1;
	if (!ft_strncmp(tolower_str(cmd), "exit", 4))
		exit(0);
	built_in = ft_split("echo cd pwd export unset env", ' ');
	while (built_in && built_in[++i])
		if (!ft_strncmp(tolower_str(cmd), built_in[i], ft_strlen(built_in[i])))
			vars->built_in = 1;
}

/*	Faire le lexer qui va séparer les arguments reçus en input
	Les mettre dans un double array
	Envoyer les args dans leur fonction respective(Adapter les fonctions déjà faites 
*/
void	filter_input(t_vars *vars, char *input)
{
	char	**args;

	args = ft_split(input, ' ');
	check_built_in(vars, args[0]);
	vars->cmd = ft_strdup(args[0]);
	free(args);
	build_lexer(vars, input);
}

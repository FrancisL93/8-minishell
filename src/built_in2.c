/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:17:18 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/22 10:17:38 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export(t_vars *vars, char *input)
{
	int		i;
	int		init;
	char	*var;
	t_list	*head;

	head = vars->var;
	if (input == NULL)
		return ;
	init = ft_strichr(input, '=');
	if (init > 0)
	{
		i = 0;
		while (vars->env[i] && ft_strncmp(vars->env[i],
				input, init))
			i++;
		if (!vars->env[i])
			export_to_env(vars, input, get_variable(vars, input));
		else
		{
			free(vars->env[i]);
			vars->env[i] = ft_strdup(input);
		}
	}
	else
	{
		var = get_variable(vars, input);
		export_to_env(vars, input, get_variable(vars, input));
	}
	vars->var = head;
}

void	unset(t_vars *vars, char *variable)
{
	int		i;
	int		ii;
	char	**env;

	i = 0;
	ii = 0;
	if (ft_strichr(variable, '=') != -1)
	{
		printf("%s: not a valid identifier\n", variable);
		return ;
	}
	while (vars->env[i] != NULL)
	{
		if (!ft_strncmp(vars->env[i], variable, ft_strlen(variable)))
			i++;
		i++;
		ii++;
	}
	env = malloc((sizeof(char *) * ii) + 1);
	i = -1;
	ii = 0;
	while (vars->env[++i] != NULL)
	{
		if (!ft_strncmp(vars->env[i], variable, ft_strlen(variable)))
			i++;
		env[ii++] = ft_strdup(vars->env[i]);
		free(vars->env[i]);
	}
	free (vars->env);
	env[ii] = NULL;
	vars->env = malloc((sizeof(char *) * ii) + 1);
	i = -1;
	while (env[++i] != NULL)
		vars->env[i] = ft_strdup(env[i]);
	vars->env[i] = NULL;
}
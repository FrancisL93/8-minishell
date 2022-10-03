/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:46:04 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/30 11:11:14 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset_len(t_vars *vars, char *variable, int *ii)
{
	int	i;

	i = 0;
	while (vars->env[i] != NULL)
	{
		if (!ft_strncmp(vars->env[i], variable, ft_strlen(variable)))
			i++;
		i++;
		*ii += 1;
	}
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
	unset_len(vars, variable, &ii);
	env = malloc((sizeof(char *) * ii) + 1);
	set_new_env(vars, variable, env, &ii);
	vars->env = malloc((sizeof(char *) * ii) + 1);
	i = -1;
	while (env[++i] != NULL)
		vars->env[i] = ft_strdup(env[i]);
	vars->env[i] = NULL;
}

void	export_new_var(t_vars *vars, char *input, int init)
{
	int	i;

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

void	export(t_vars *vars, char *input)
{
	int		init;
	char	*var;
	t_list	*head;

	head = vars->var;
	if (input == NULL)
		return ;
	init = ft_strichr(input, '=');
	if (init > 0)
		export_new_var(vars, input, init);
	else
	{
		var = get_variable(vars, input);
		export_to_env(vars, input, get_variable(vars, input));
	}
	vars->var = head;
}
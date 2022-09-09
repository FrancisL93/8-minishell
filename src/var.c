/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:25 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/08 12:02:50 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_to_env(t_vars *vars, char *variable)
{
	int		i;
	char	**env;

	i = 0;
	if (!variable)
		return ;
	while (vars->env[i])
		i++;
	env = malloc(sizeof(char**) * (i + 2));
	i = -1;
	while (vars->env[++i])
	{
		env[i] = ft_strdup(vars->env[i]);
		free(vars->env[i]);
	}
	free(vars->env);
	vars->env = malloc(sizeof(char **) * (i + 2));
	i = -1;
	while (env[++i])
		vars->env[i] = ft_strdup(env[i]);
	vars->env[i++] = ft_strdup(variable);
	vars->env[i] = NULL;
}

char	*use_variable(t_vars *vars, char *var)
{
	t_list	*tmp;
	char	*var_content;
	int		i;

	i = 0;
	while (ft_strncmp(vars->env[i], var, ft_strlen(var)))
		i++;
	if (vars->env[i])
	{
		var_content = &vars->env[i][ft_strlen(var)+1];
		return (var_content);
	}
	tmp = vars->var;
	while (tmp && ft_strncmp(var, tmp->content, ft_strlen(var)))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	else
	{
		var_content = &tmp->content[ft_strlen(var) + 1];
		return (var_content);
	}
}

void	add_variable(t_vars *vars, char *variable)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (variable[i] != '=')
		i++;
	while (vars->env[j] && ft_strncmp(vars->env[j], variable, i))
		j++;
	if (!vars->env[j])
		ft_lstadd_front(&vars->var, ft_lstnew(variable));
	else
		vars->env[i] = variable;
}

char	*get_variable(t_vars *vars, char *variable)
{
	char	*var;
	int		varlen;
	int		i;

	i = -1;
	varlen = 0;
	if (!variable || !variable[1])
		return (NULL);
	var = &variable[1];
	while (var[varlen] && var[varlen] != ' ')
		varlen++;
	while (vars->env[++i])
		if (!ft_strncmp(vars->env[i], var, varlen))
			return (vars->env[i]);
	while (vars->var && vars->var->content)
	{
		if (!ft_strncmp(vars->var->content, var, varlen))
			return (vars->var->content);
		vars->var = vars->var->next;
	}
	return (NULL);
}
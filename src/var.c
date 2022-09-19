/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:25 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/19 09:30:25 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// afficher env si !varible sinon export variable if variable existe || variable définie au moment d'export
void	export_to_env(t_vars *vars, char *variable)
{
	int		i;
	char	**env;

	i = 0;
	if (!variable)
		return ;
	while (vars->env[i])
		i++;
	env = malloc(sizeof(char **) * (i + 2));
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
		var_content = &vars->env[i][ft_strlen(var) + 1];
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

int	add_variable(t_vars *vars, char *variable)
{
	int	nlen;
	int	j;

	nlen = 0;
	j = 0;
	if (variable != NULL)
	{
		while (variable[nlen] != '=')
			nlen++;
		if (variable[nlen] == '\0')
			return (0);
		ft_lst_add_front(&vars->var, ft_lst_new(ft_str_dup(&variable[nlen + 1]),
				ft_strndup(variable, nlen)));
	}
	return (1);
}

char	*get_variable(t_vars *vars, char *dolvar)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = dolvar_len(&dolvar[1]);
	while (vars->env[i] != NULL)
	{
		if (!ft_strncmp(&dolvar[1], vars->env[i], len))
			return (&vars->env[i][len + 2]);
		i++;
	}
	while (vars->var != NULL)
	{
		if (!ft_strncmp(&dolvar[1], vars->var->name, len))
			return (vars->var->content);
		vars->var = vars->var->next;
	}
	return (NULL);
}

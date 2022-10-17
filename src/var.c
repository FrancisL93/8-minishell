/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:25 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/17 10:37:08 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	create_new_env(t_vars *vars, char *new_var, int i, int ii)
{
	char	**env;

	while (vars->env[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (vars->env[++i] != NULL)
	{
		if (vars->env[i + 1] == NULL)
			env[ii++] = new_var;
		env[ii++] = ft_strdup(vars->env[i]);
		free(vars->env[i]);
	}
	free(vars->env);
	env[i + 1] = NULL;
	vars->env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (env[++i] != NULL)
	{
		vars->env[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	free(env);
	vars->env[i] = NULL;
}

void	export_to_env(t_vars *vars, char *input, char *variable)
{
	char	*new_var;
	char	*tmp;
	int		i;
	int		ii;

	i = 0;
	ii = 0;
	if (!variable && ft_strichr(input, '=') == -1)
	{
		if (get_variable(vars, input) != NULL)
			new_var = ft_strjoin(input, "=");
		else
			return ;
	}
	else if (!variable && ft_strichr(input, '='))
		new_var = ft_strdup(input);
	else
	{
		tmp = ft_strjoin(input, "=");
		new_var = ft_strjoin(tmp, variable);
		free (tmp);
	}
	create_new_env(vars, new_var, i, ii);
}

int	add_variable(t_vars *vars, char *variable)
{
	int	nlen;
	int	i;

	nlen = 0;
	i = 0;
	if (variable == NULL)
		return (0);
	while (variable[nlen] != '=')
		nlen++;
	if (variable[nlen] == '\0')
		return (1);
	while (vars->env[i] != NULL && variable != NULL
		&& ft_strncmp(variable, vars->env[i], nlen))
		i++;
	if (vars->env[i] != NULL)
	{
		free(vars->env[i]);
		vars->env[i] = ft_str_dup(variable);
	}
	else
		ft_lst_add_front(&vars->var, ft_lst_new(ft_str_dup(&variable[nlen + 1]),
				ft_strndup(variable, nlen)));
	free(variable);
	return (0);
}

//Retrieve $var from shell environement or local variables
char	*get_variable(t_vars *vars, char *dolvar)
{
	int	len;
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (dolvar[0] != 36)
		len = ft_str_len(dolvar);
	else
	{
		len = dolvar_len(&dolvar[1]);
		j = 1;
	}
	while (vars->env[++i] != NULL)
		if (!ft_strncmp(&dolvar[j], vars->env[i], len))
			return (&vars->env[i][len + 1]);
	while (vars->var != NULL)
	{
		if (!ft_strncmp(&dolvar[j], vars->var->name, len))
			return (vars->var->content);
		vars->var = vars->var->next;
	}
	return (NULL);
}

//Check if $var in input is present in env or local variables, and add it
//Return if $var is in a pipe command
int	check_var(t_vars *vars, int i)
{
	int		j;
	int		ret;

	j = 0;
	if (vars->pipe > 1)
		return (1);
	ret = add_variable(vars, ft_strdup(vars->cmds[i].cmds[j]));
	while (vars->cmds[i].cmds[j])
	{
		if (ft_strichr(vars->cmds[i].cmds[j], '=') < 0)
			j++;
		else
		{
			add_variable(vars, ft_strdup(vars->cmds[i].cmds[j]));
			j++;
		}
	}
	if (ret == 0)
		return (1);
	return (0);
}

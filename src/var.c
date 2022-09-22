/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:25 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/22 10:24:33 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_to_env(t_vars *vars, char *input, char *variable)
{
	int		i;
	int		ii;
	char	*new_var;
	char	**env;

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
		new_var = input;
	else
		new_var = ft_strjoin(ft_strjoin(input, "="), variable);
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
	int	i;
	int	j;

	nlen = 0;
	i = 0;
	j = 0;
	if (variable != NULL)
	{
		while (variable[nlen] != '=')
			nlen++;
		if (variable[nlen] == '\0')
			return (0);
		ft_lst_add_front(&vars->var, ft_lst_new(ft_str_dup(&variable[nlen + 1]),
				ft_strndup(variable, nlen)));
		while (vars->env[i] != NULL && ft_strncmp(variable, vars->env[i], nlen))
			i++;
		if (vars->env[i] != NULL)
		{
			free(vars->env[i]);
			vars->env[i] = ft_str_dup(variable);
		}
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
	if (dolvar[0] != 36)
		len = ft_strlen(dolvar);
	else
	{
		len = dolvar_len(&dolvar[1]);
		j = 1;
	}
	while (vars->env[i] != NULL)
	{
		if (!ft_strncmp(&dolvar[j], vars->env[i], len))
			return (&vars->env[i][len + 1]);
		i++;
	}
	while (vars->var != NULL)
	{
		if (!ft_strncmp(&dolvar[j], vars->var->name, len))
			return (vars->var->content);
		vars->var = vars->var->next;
	}
	return (NULL);
}

int	check_var(t_vars *vars, int i)
{
	int		j;
	int		res;

	j = -1;
	if (i != vars->pipe - 1)
		return (1);
	while (vars->cmds[i].cmds[++j])
	{
		res = add_variable(vars, vars->cmds[i].cmds[j]);
		if (res == 1)
			return (1);
	}
	return (0);
}
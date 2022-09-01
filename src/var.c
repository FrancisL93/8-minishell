/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:49:03 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/01 17:09:20 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Envoyer la variable sans le =, exemple var=3, envoyer "var, if NULL returned, print \n
char	*use_variable(t_vars *vars, char *var)
{
	t_list	*tmp;
	char	*var_content;
	int		i;

	i = 0;
	while (ft_strncmp(environ[i], var, ft_strlen(var)))
		i++;
	if (environ[i])
	{
		var_content = &environ[i][ft_strlen(var)+1];
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
	while (environ[j] && ft_strncmp(environ[j], variable, i))
		j++;
	if (!environ[j])
		ft_lstadd_front(&vars->var, ft_lstnew(variable));
	else
		environ[i] = variable;
}

char	*get_variable(t_vars *vars, char *variable)
{
	char	*cmd;
	char	*var;

	var = &variable[1];
	cmd = (char *) vars->var->content;
	ft_putstr_fd(cmd, STDERR_FILENO);
	while (cmd)
	{
		ft_putstr_fd("salut2", STDERR_FILENO);
		if (!ft_strncmp(cmd, var, ft_strlen(var)))
			return (cmd);
		vars->var = vars->var->next;
		cmd = (char *) vars->var->content;
	}
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:48:55 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/06 13:50:29 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->env[i] != NULL)
	{
		if (!strncmp("PATH", vars->env[i], 4))
			break ;
		i++;
		if (vars->env[i] == NULL)
		{
			printf("env: %s\n", strerror(ENOENT));
			vars->exit_stat = 127;
			return ;
		}
	}
	i = -1;
	while (vars->env[++i] != NULL)
		printf("%s\n", vars->env[i]);
}

void	print_path(void)
{
	char	*buff;
	char	*ret;

	buff = NULL;
	ret = getcwd(buff, 1024);
	printf("%s\n", ret);
	free(ret);
	free (buff);
}

void	set_pwd(t_vars *vars, char *oldpath)
{
	int		i;
	char	*buff;

	buff = NULL;
	i = 0;
	while (vars->env[i] && ft_strncmp(vars->env[i], "PWD=", 4))
		i++;
	if (vars->env[i])
	{
		free(vars->env[i]);
		vars->env[i] = ft_strjoin("PWD=", getcwd(buff, 1024));
		free(buff);
	}
	if (vars->env[i] != NULL)
	{
		if (ft_strncmp(vars->env[i + 1], "OLDPWD", 6))
		{
			buff = ft_strjoin("OLDPWD=", oldpath);
			export(vars, buff);
			free(buff);
			return ;
		}
	}
	i = 0;
	while (vars->env[i] && ft_strncmp(vars->env[i], "OLDPWD=", 7))
		i++;
	if (vars->env[i])
	{
		free(vars->env[i]);
		vars->env[i] = ft_strjoin("OLDPWD=", oldpath);
	}
}

void	set_new_env(t_vars *vars, char *variable, char **env, int *ii)
{
	int	i;

	i = -1;
	*ii = 0;
	while (vars->env[++i] != NULL)
	{
		if (!ft_strncmp(vars->env[i], variable, ft_strlen(variable)))
		{
			free(vars->env[i]);
			i++;
		}
		env[*ii] = ft_strdup(vars->env[i]);
		*ii += 1;
		free(vars->env[i]);
	}
	free (vars->env);
	env[*ii] = NULL;
}

int	set_env(t_vars *vars, char **envp)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	while (envp[i])
		i++;
	vars->env = malloc(sizeof(char *) * (i + 1));
	if (!vars->env)
		return (1);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("OLDPWD", envp[i], 6))
			i++;
		vars->env[ii] = ft_strdup(envp[i]);
		ii++;
	}
	vars->env[ii] = NULL;
	return (0);
}

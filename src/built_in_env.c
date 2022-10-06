/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:48:55 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/06 16:00:25 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_env(t_vars *vars)
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
			return (1);
		}
	}
	i = -1;
	while (vars->env[++i] != NULL)
		printf("%s\n", vars->env[i]);
	return (1);
}

int	print_path(void)
{
	char	*buff;
	char	*ret;

	buff = NULL;
	ret = getcwd(buff, 1024);
	printf("%s\n", ret);
	free(ret);
	free (buff);
	return (1);
}

void	set_pwd(t_vars *vars, char *oldpath)
{
	int		i;
	char	*buff;
	char	*cwd;

	i = 0;
	buff = NULL;
	cwd = getcwd(buff, 1024);
	export(vars, ft_strjoin("PWD=", cwd));
	free(cwd);
	export(vars, ft_strjoin("OLDPWD=", oldpath));
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

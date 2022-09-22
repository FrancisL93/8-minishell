/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:40:37 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/22 09:48:09 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_flag(char *flag)
{
	int	i;

	i = 0;
	while (flag[i])
	{
		if (flag[0] != '-')
			return (0);
		i++;
		if (flag[1] != 'n')
			return (0);
		i++;
		if (flag[2] == '\0')
			return (1);
		if (flag[2] != 'n' && flag[2] != ' ')
			return (0);
		while (flag[i] == 'n')
		{
			i++;
			if (flag[i] == ' ' || flag[i] == '\0')
				return (1);
		}
	}
	return (0);
}

void	echo(t_vars *vars, int i)
{
	int	j;
	int	nl;

	j = 1;
	nl = 1;
	if (vars->cmds[i].cmds[j] == NULL)
		printf("\n");
	while (check_flag(vars->cmds[i].cmds[j]) == 1)
		j++;
	if (j != 1)
		nl = 0;
	while (vars->cmds[i].cmds[j] != NULL)
	{
		printf("%s", vars->cmds[i].cmds[j]);
		j++;
		if (vars->cmds[i].cmds[j] != NULL)
			printf(" ");
		if (vars->cmds[i].cmds[j] == NULL)
		{
			if (nl == 1)
				printf("\n");
		}
	}
}

// pwd
void	print_path(void)
{
	char	*buff;

	buff = NULL;
	printf("%s\n", getcwd(buff, 1024));
	free (buff);
}

// env
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
			return ;
	}
	i = -1;
	while (vars->env[++i] != NULL)
		printf("%s\n", vars->env[i]);
}

//cd
void	cd(t_vars *vars, char *input)
{
	char	buff[1024];
	char	*current_path;
	char	*new_path;
	char	*oldpath;

	oldpath = getcwd(buff, 1024);
	current_path = getcwd(buff, 1024);
	if (!input)
		new_path = ft_strchr(getenv("HOME="), '/');
	else if (input[0] == '.')
		new_path = check_path(input, current_path);
	else if (ftstrnstr(current_path, input) != 0)
		new_path = input;
	else if (ft_strlen(input) == 1 && input[0] == '/')
		new_path = input;
	else
		new_path = ftstrjoin(input, current_path);
	if (chdir(new_path) != 0)
	{
		printf("Not a directory\n");
		return ;
	}
	set_pwd(vars, oldpath);
}

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

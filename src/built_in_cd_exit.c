/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:40:37 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/06 09:56:44 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_path(char *cmd, char *current_path)
{
	char	*buff;

	buff = NULL;
	if (cmd[0] == '.' && cmd[1] == '\0')
		return (getcwd(buff, 1024));
	else if (ft_strlen(current_path) == 1 && current_path[0] == '/')
		return (current_path);
	else if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '\0')
		return (ftstrtrim(current_path));
	else if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		return (ft_strjoin(ftstrtrim(current_path), strdup(&cmd[2])));
	return (NULL);
}

void	check_dir(t_vars *vars, char *path)
{
	int		i;
	char	*new_path;

	i = 0;
	while (vars->env[i] != NULL)
	{
		if (strncmp(vars->env[i], "PWD", 3) == 0)
			return ;
		i++;
	}
	new_path = ft_strjoin("PWD=", path);
	export(vars, new_path);
}

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
	check_dir(vars, new_path);
	if (chdir(new_path) != 0)
	{
		printf("cd: %s: %s\n", input, strerror(ENOTDIR));
		add_exit(vars, 127);
		return ;
	}
	set_pwd(vars, oldpath);
}

void	ft_exit(t_vars *vars, char *exit_status)
{
	int	i;

	i = 0;
	while (exit_status[i])
	{
		if (!ft_isdigit(exit_status[i]))
		{
			printf("exit: %s: numeric argument required\n", exit_status);
			quit_terminal(vars, 255);
		}
		i++;
		if (exit_status[i] == '\0')
			add_exit(vars, ft_atoi(exit_status));
	}
	quit_terminal(vars, ft_atoi(exit_status));
}

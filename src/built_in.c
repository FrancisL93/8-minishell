/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:40:37 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/22 10:36:18 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	print_path(void)
{
	char	*buff;

	buff = NULL;
	printf("%s\n", getcwd(buff, 1024));
	free (buff);
}

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

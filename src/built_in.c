/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:40:37 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/20 08:55:33 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// utiliser ft_putstr_fd plutot que printf et envoyer dans le outfile

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
/* 	else if (input[0] == 36)
	{
		if (get_variable(vars, input) == NULL)
			new_path = ft_strchr(getenv("HOME="), '/');
		else
			new_path = get_variable(vars, input);
	} */
	else if (ftstrnstr(current_path, input) != 0)
		new_path = input;
	else if (ft_strlen(input) == 1 && input[0] == '/')
		new_path = input;
	else
		new_path = ftstrjoin(input, current_path);
	if (chdir(new_path) != 0)
	{
		//free(new_path);
		printf("Not a directory\n");
		return ;
	}
	//free(new_path);
	set_pwd(vars, oldpath);
	// Faire une fonction pour tout free
/*	free (new_path);
	free (cmd);
	free (current_path); */
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

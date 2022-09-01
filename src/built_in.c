/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:40:37 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/01 17:00:12 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// echo (Implementer $ sign)
/* void	echo(char *str)
{
	int	n_l;
	int	i;

	i = 5;
	n_l = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		n_l = 0;
		i += 2;
	}
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		while (str[i] == ' ' && str[i + 1] == ' ')
			i++;
		if (str[i] == ' ' && str[i + 1] == '\0')
			break ;
		printf("%c", str[i]);
		i++;
	}
	if (n_l == 1)
		printf("\n");
} */

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

void	echo(t_vars *vars)
{
	int	n_l;
	int	i;
	int	n_flag;

	i = 1;
	n_l = 1;
	n_flag = 0;
	while (i < vars->nb_tokens)
	{
		if (check_flag(vars->token.tokens[i]) == 1 && n_flag == 0)
			n_l = 0;
		else
		{
			printf("%s", vars->token.tokens[i]);
			if (i + 1 != vars->nb_tokens)
				printf(" ");
			n_flag = 1;
		}
		i++;
	}
	if (n_l == 1)
		printf("\n");
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
void	print_env(void)
{
	int	i;

	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);
}

//cd
void	cd(char *input)
{
	char	*buff;
	char	*current_path;
	char	*new_path;
	char	*cmd;
	char	*oldpath;

	buff = NULL;
	oldpath = getcwd(buff, 1024);
	cmd = get_cmd(input);
	current_path = getcwd(buff, 1024);
	if (cmd[0] == '\0')
		new_path = ft_strchr(getenv("HOME="), '/');
	else if (cmd[0] == '.')
		new_path = check_path(cmd, current_path);
	else if (ftstrnstr(current_path, cmd) != 0)
		new_path = cmd;
	else if (ft_strlen(cmd) == 1 && cmd[0] == '/')
		new_path = cmd;
	else
		new_path = ftstrjoin(cmd, current_path);
	if (chdir(new_path) != 0)
	{
		printf("Not a directory\n");
		return ;
	}
	set_pwd(oldpath);
	// Faire une fonction pour tout free
/*	free (buff);
	free (new_path);
	free (cmd);
	free (current_path); */
}

void	export(t_vars *vars)
{
	int		i;
	int		j;
	int		init;
	char	*var;
	
	i = 0;
	j = 0;
	while (vars->token.tokens[++j] != NULL)
	{
		if (!vars->token.tokens[j])
			return ;
		init = ft_strichr(vars->token.tokens[j], '=');
		if (init > 0)
		{
			while (environ[i] && ft_strncmp(environ[i], vars->token.tokens[j], init))
				i++;
			if (!environ[i])
				export_to_env(vars->token.tokens[j++]);
			else
				environ[i] = ft_strdup(vars->token.tokens[j++]);
			i = 0;
		}
		else if (vars->token.tokens[j][0] == '$')
		{
			var = get_variable(vars, vars->token.tokens[j]);
			printf("%s\n", var);
		}
		//	export_to_env(get_variable(vars, vars->token.tokens[j]));
	}
	return ;
}

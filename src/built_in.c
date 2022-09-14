/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:40:37 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/14 11:41:58 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// utiliser ft_putstr_fd plutot que printf et envoyer dans le outfile

// echo (Implementer $ sign)
/* void	print_echo(char *str)
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

void	echo(t_vars *vars, int i)
{
	int	j;
	int	nl;

	j = 1;
	nl = 1;
	while (check_flag(vars->cmds[i].cmds[j]) == 1)
		j++;
	if (j != 1)
		nl = 0;
	while (vars->cmds[i].cmds[j] != NULL)
	{
		if (vars->cmds[i].cmds[j + 1] == NULL && nl == 1)
		{
			if (nl == 1)
				printf("%s\n", vars->cmds[i].cmds[j]);
			else if (nl == 0)
				printf("%s", vars->cmds[i].cmds[j]);
			break ;
		}
		printf("%s ", vars->cmds[i].cmds[j]);
		j++;
	}
}

/* void	echo(t_vars *vars)
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
} */

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
	while (vars->env[++i])
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
			while (vars->env[i] && ft_strncmp(vars->env[i],
					vars->token.tokens[j], init))
				i++;
			if (!vars->env[i])
				export_to_env(vars, vars->token.tokens[j++]);
			else
			{
				free(vars->env[i]);
				vars->env[i] = ft_strdup(vars->token.tokens[j++]);
			}
			i = 0;
		}
		else if (vars->token.tokens[j][0] == '$')
		{
			var = get_variable(vars, vars->token.tokens[j]);
			export_to_env(vars, get_variable(vars, vars->token.tokens[j]));
		}
	}
	return ;
}

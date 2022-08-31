/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:40:37 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/31 12:23:01 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// echo (Implementer $ sign)
void	echo(char *str)
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

void	export(char *input)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = -1;
	k = 6;
	tmp = malloc(sizeof(char) * ft_strlen(input - 6));
	while (input[k] == ' ')
		k++;
	while (input[k + ++j])
		tmp[j] = input[k + j];
	while (input[j] == ' ')
		j++;
	while (environ[i])
		i++;
	environ[i] = tmp;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:48:08 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/01 13:04:58 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*tolower_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] >= 65 && str[i] <= 90)
			str[i] += 32;
	return (str);
}

char	*get_cmd(char *input)
{
	int		i;
	int		j;
	char	*cmd;

	i = 2;
	j = 0;
	cmd = calloc(sizeof(char), ft_strlen(input) - 2);
	while (input[i] == ' ')
		i++;
	while (input[i] != ' ' && input[i])
	{
		cmd[j] = input[i];
		j++;
		i++;
	}
	return (cmd);
}

void	set_prompt(t_vars *vars)
{
	int		i;
	char	*prompt;

	prompt = getenv("PWD");
	i = ft_strlen(prompt) - 1;
	while (prompt[i] != '/')
		i--;
	vars->prompt = ft_strjoin("\e[1;34m", &prompt[i]);
	vars->prompt = ft_strjoin(vars->prompt, " >> \e[0;37m");
}

void	realloc_env(int	new)
{
	int		i;
	char	**env;

	i = 0;
	while (environ[i])
		i++;
	env = malloc(sizeof(char**) * (i));
	i = -1;
	while (environ[++i])
		env[i] = ft_strdup(environ[i]);
	environ = malloc(sizeof(char **) * (i + new));
	i = -1;
	while (env[++i])
		environ[i] = ft_strdup(env[i]);
}

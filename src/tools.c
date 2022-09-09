/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:28:04 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/09 14:14:20 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*tolower_str(char *str, int capital)
{
	int	i;

	i = -1;
	if (capital)
	{
		while (str[++i])
			if (str[i] >= 97 && str[i] <= 122)
				str[i] -=32;
	}
	else
	{
		while (str[++i])
			if (str[i] >= 65 && str[i] <= 90)
				str[i] += 32;
	}
	return (str);
}

void	set_prompt(t_vars *vars)
{
	int		i;
	char	*prompt;
	char	*tmp;

	prompt = getenv("PWD");
	i = ft_strlen(prompt) - 1;
	while (prompt[i] != '/')
		i--;
	tmp = ft_strjoin("\e[1;34m", &prompt[i]);
	vars->prompt = ft_strjoin(tmp, " >> \e[0;37m");
	free(tmp);
}

int	ft_strichr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != (char) c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
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

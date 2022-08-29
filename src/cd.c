/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:39:20 by anhebert          #+#    #+#             */
/*   Updated: 2022/08/29 11:44:46 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}

int	ftstrnstr(char *current_path, char *cmd)
{
	int	i;
	int	ii;

	i = -1;
	ii = 0;
	while (current_path[++i])
	{
		if (cmd[ii] != current_path[i])
			return (0);
		ii++;
		if (cmd[ii] == '\0')
			break ;
	}
	return (1);
}

char	*ftstrjoin(char *cmd, char *current_path)
{
	int		i;
	int		j;
	int		size;
	char	*new_path;

	i = -1;
	j = 0;
	size = ft_strlen(current_path);
	size += ft_strlen(cmd);
	new_path = calloc(sizeof(char), size + 2);
	while (current_path[++i])
	{
		new_path[j] = current_path[i];
		j++;
	}
	new_path[j] = '/';
	i = -1;
	j++;
	while (cmd[++i])
	{
		new_path[j] = cmd[i];
		j++;
	}
	return (new_path);
}

char	*ftstrtrim(char	*current_path)
{
	int		i;
	int		ii;
	int		j;
	char	*new_path;

	i = 0;
	ii = 0;
	j = 0;
	new_path = calloc(sizeof(char), ft_strlen(current_path));
	while (current_path[i])
		i++;
	while (current_path[i] != '/')
		i--;
	while (ii < i)
	{
		new_path[j] = current_path[ii];
		j++;
		ii++;
	}
	return (new_path);
}

char	*check_path(char *cmd, char *current_path)
{
	if (cmd[0] == '.' && cmd[1] == '\0')
		return (current_path);
	else if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '\0')
		return (ftstrtrim(current_path));
	return (NULL);
}

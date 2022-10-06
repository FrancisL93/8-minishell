/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:39:20 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/06 14:26:19 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	echo_built(t_vars *vars, int i)
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
	return (1);
}

int	check_flag(char *flag)
{
	int	i;

	i = 0;
	while (flag && flag[i])
	{
		if (flag[0] != '-')
			return (0);
		i++;
		if (flag[1] != 'n')
			return (0);
		i++;
		if (flag[2] == '\0')
			return (1);
		if (flag[2] != 'n' && !is_space(flag[2]))
			return (0);
		while (flag[i] == 'n')
		{
			i++;
			if (is_space(flag[i]) || flag[i] == '\0')
				return (1);
			if (flag[i] == '-')
				return (0);
		}
	}
	return (0);
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
	new_path = ft_calloc(sizeof(char), size + 2);
	if (!new_path)
		return (NULL);
	while (current_path[++i])
		new_path[j++] = current_path[i];
	new_path[j] = '/';
	i = -1;
	while (cmd[++i])
		new_path[++j] = cmd[i];
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
	new_path = ft_calloc(sizeof(char), ft_strlen(current_path));
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

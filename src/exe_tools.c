/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:39:03 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/03 10:28:19 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	search_infile(t_vars *vars, int i, int ii)
{
	if (vars->args[i][ii] && vars->args[i][ii][0] == '<')
	{
		if (vars->args[i][ii + 1] && vars->args[i][ii + 1][0] == '<')
			return (0);
		if (vars->args[i][ii + 1])
		{
			vars->cmds[i].fd[0] = open(vars->args[i][ii + 1], O_RDONLY, 0777);
			if (vars->cmds[i].fd[0] == -1)
			{
				perror("Error pizza");
				return (1);
			}
		}
		else
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}

int	search_outfile(t_vars *vars, int i, int *ii)
{
	if (vars->args[i][*ii] && vars->args[i][*ii][0] == '>')
	{	
		if (vars->args[i][*ii + 2] && vars->args[i][*ii + 1][0] == '>')
		{
			if (put_fds(vars, i, ii, 1) == 1)
				return (1);
		}
		else if (vars->args[i][*ii + 1] && vars->args[i][*ii + 1][0] != '>')
		{
			if (put_fds(vars, i, ii, 2) == 1)
				return (1);
		}
		else
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
	}
	return (0);
}

char	*ft_strndup(char *str, unsigned int n)
{
	char				*dup;
	unsigned int		i;

	i = 0;
	dup = malloc(sizeof(char) * (n + 1));
	while (i < n)
		dup[i++] = *str++;
	dup[n] = 0;
	return (dup);
}

char	*join_path(char *path, char *bin)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char)
			* (ft_strichr(path, 0) + ft_strichr(bin, 0) + 2));
	i = 0;
	j = 0;
	while (path[j])
		joined[i++] = path[j++];
	joined[i++] = '/';
	j = 0;
	while (bin[j])
		joined[i++] = bin[j++];
	joined[i] = '\0';
	return (joined);
}

char	*get_path(char *cmnd, char **envp)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	if (!cmnd)
		return (NULL);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (cmnd);
	path = envp[i] + 5;
	while (path && ft_strichr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strichr(path, ':'));
		bin = join_path(dir, cmnd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	return (cmnd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:39:03 by flahoud           #+#    #+#             */
/*   Updated: 2022/10/11 14:08:39 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	free(path);
	return (joined);
}

//Get path of command if no "/"
char	*get_path(char *path, char *cmnd, char **envp)
{
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!cmnd || !envp[i])
		return (cmnd);
	path = envp[i] + 5;
	while (path)
	{
		if (ft_strichr(path, ':') > -1)
			dir = ft_strndup(path, ft_strichr(path, ':'));
		else
			dir = ft_strdup(path);
		bin = join_path(dir, cmnd);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		if (ft_strichr(path, ':') < 0)
			break ;
		path += ft_strichr(path, ':') + 1;
	}
	return (cmnd);
}

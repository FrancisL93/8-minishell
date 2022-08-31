/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:00:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/08/31 12:20:08 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//Modifications from francis branch

int	init_struct(t_vars *vars)
{
	char	*tmp_path;
	
	tmp_path = ft_strjoin(getenv("TMPDIR"), "heredoc_minishell");
	vars->heredoc_fd = open(tmp_path, O_RDWR, O_CREAT);
	set_prompt(vars);
	vars->built_in = 0;
	vars->pipe = 0;
	free(tmp_path);
	return (0);
}

void	test()
{
	char	*input;

	input = readline("Test: ");
	printf("%d\n", chdir("/"));
	printf("%s", get_cmd(input));
}

int	main(int argc, char **argv)
{
	char	*input;
	t_vars	vars;

	if (argc == 2 && !ft_strncmp(argv[1], "test", 4))
		test();
	else if (argc == 1 && argv[0])
	{
		if (init_struct(&vars))
			return (1);
		printf("%s", CLEAN);
		input = readline(vars.prompt);
		while (input)
		{
			if (input && *input)
				add_history(input);
			filter_input(&vars, input);
			lexer(input, &vars);
			if (execute(&vars, input))
				exit(1);
			set_prompt(&vars);
			free(input);
			input = readline(vars.prompt);
		}	
	}
	else
		printf("Error: Execute as ./minishell\n");
	return (1);
}

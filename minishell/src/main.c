/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:00:52 by flahoud           #+#    #+#             */
/*   Updated: 2022/09/01 11:34:18 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//Modifications from francis branch

int	init_struct(t_vars *vars)
{
	char	*tmp_path;

	tmp_path = ft_strjoin(getenv("TMPDIR"), "heredoc_minishell");
	printf("%s\n", tmp_path);
	vars->heredoc_fd = open(tmp_path, O_TRUNC| S_IRUSR | S_IWUSR, 0777);
	printf("%d\n", vars->heredoc_fd);
	set_prompt(vars);
	vars->built_in = 0;
	vars->pipe = 0;
	free(tmp_path);
	return (0);
}

void	test()
{
	t_vars	vars;
	char	*input;
	char	*str;

	if (init_struct(&vars))
		return ;
	input = readline("Test: ");
	ft_putstr_fd("salut", vars.heredoc_fd);
	str = get_next_line(vars.heredoc_fd);
	printf("%s\n", str);

	//printf("%d\n", chdir("/"));
	//printf("%s", get_cmd(input));
	//add_variable(&vars, input);
	//export(&vars, input);
	//print_env();
	exit(0);
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
			lexer(input, &vars);
			filter_tokens(&vars);
			if (execute(&vars, input))
				exit(1);
			set_prompt(&vars);
			free(input);
			vars.built_in = 0;
			input = readline(vars.prompt);
		}	
	}
	else
		printf("Error: Execute as ./minishell\n");
	return (1);
}

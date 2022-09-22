/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:59:00 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/20 16:11:05 by flahoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/inc/libft.h"
# include "stdio.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "errno.h"
# include "signal.h"
# include "sys/ioctl.h"

# define CLEAN "\e[1;1H\e[2J"
# define BLUE "\e[1;34m"
# define GREEN "\e[1;32m"
# define IN 0
# define OUT 1

typedef struct s_cmds
{
	char				*cmd;
	char				**cmds;
	int					index;
	pid_t				pid;
}					t_cmds;

typedef struct s_token
{
	char	**tokens;
}	t_token;

typedef struct s_vars
{
	char	***args;
	char	**env;
	char	*prompt;
	int		*fd;
	int		pipe;
	int		nb_tokens;
	int		token_len;
	char	*heredoc_eof;
	int		pipe_num;
	int		**pipefd;
	pid_t	*pid;
	t_list	*var;
	t_token	token;
	t_cmds	*cmds;
}t_vars;

typedef struct s_indexes
{
	int	i;
	int	ii;
	int	j;
	int	jj;
}	t_indexes;

//built_in.c
void	cd(t_vars *vars, char *input);
void	print_env(t_vars *vars);
void	print_path(void);
void	echo(t_vars *vars, int i);
void	export(t_vars *vars, char *input);

//built_in_tools.c
void	set_pwd(t_vars *vars, char *oldpath);
int		ftstrnstr(char *current_path, char *cmd);
char	*ftstrjoin(char *cmd, char *current_path);
char	*ftstrtrim(char	*current_path);
char	*check_path(char *cmd, char *current_path);

//built_in_tools2.c
int		check_flag(char *flag);

//cmds_tools.c
void	split_cmds(t_vars *vars);
int		dolvar_len(char *token);

//exe.c
void	execute(t_vars *vars);

//exe_tools.c
char	*get_path(char *cmnd, char **envp);
char	*ft_strndup(char *str, unsigned int n);

//heredoc.c
void	check_heredoc(t_vars *vars, int i);

//lexer.c
void	lexer(char *input, t_vars *vars);

//list_tools.c
t_list	*ft_lst_new(void *content, void *name);
void	ft_lst_add_front(t_list **lst, t_list *new1);
char	*ft_str_dup(const char *str);

//quit_clean.c
void	quit_terminal(t_vars *vars, t_list *variables);
void	clean_command(t_vars *vars, char *input);
void	free_redir(t_vars *vars, int i, int ii);

//signals.c
void	init_signals(int children);
void	check_signal(t_vars *vars);

//tools.c
char	*tolower_str(char *str, int capital);
void	set_prompt(t_vars *vars);
int		ft_strichr(const char *s, int c);
char	*get_cmd(char *input);

//tools2.c
size_t	ft_str_len(const char *str);

//var.c
void	export_to_env(t_vars *vars, char *input, char *variable);
int		add_variable(t_vars *vars, char *variable);
char	*get_variable(t_vars *vars, char *variable);
char	*use_variable(t_vars *vars, char *var);

#endif
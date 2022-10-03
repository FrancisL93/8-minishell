/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:59:00 by anhebert          #+#    #+#             */
/*   Updated: 2022/10/03 12:01:19 by anhebert         ###   ########.fr       */
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
# include "termios.h"
# include "curses.h"
# include "sys/ioctl.h"

# define CLEAN "\e[1;1H\e[2J"
# define BLUE "\e[1;34m"
# define GREEN "\e[1;32m"
# define IN 0
# define OUT 1

typedef struct s_cmds
{
	char		*cmd;
	char		**cmds;
	int			fd[2];
	int			index;
	pid_t		pid;
}t_cmds;

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
	int		exit_stat;
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

//built_in_cd.c
void	cd(t_vars *vars, char *input);
void	check_dir(t_vars *vars, char *path);
char	*check_path(char *cmd, char *current_path);

//built_in_env.c
int		set_env(t_vars *vars, char **envp);
void	print_path(void);
void	print_env(t_vars *vars);
void	set_pwd(t_vars *vars, char *oldpath);
void	set_new_env(t_vars *vars, char *variable, char **env, int *ii);

//built_in_export.c
void	export(t_vars *vars, char *input);
void	export_new_var(t_vars *vars, char *input, int init);
void	unset(t_vars *vars, char *variable);
void	unset_len(t_vars *vars, char *variable, int *ii);

//built_in_tools.c
int		check_flag(char *flag);
int		ftstrnstr(char *current_path, char *cmd);
char	*ftstrjoin(char *cmd, char *current_path);
char	*ftstrtrim(char	*current_path);
void	echo_built(t_vars *vars, int i);

//check built_ins.c
int		check_built_in(t_vars *vars, int i);
int		check_export(t_vars *vars, int i);
int		check_unset(t_vars *vars, int i);
int		check_cd(t_vars *vars, int i);

//exe.c
void	execute(t_vars *vars);
void	check_cmds(t_vars *vars, int ret, int i);
void	child_process(t_vars *vars, int i);
void	execute_command(t_vars *vars, int i);

//exe_tools.c
int		search_infile(t_vars *vars, int i, int ii);
int		search_outfile(t_vars *vars, int i, int *ii);
char	*join_path(char *path, char *bin);
char	*get_path(char *cmnd, char **envp);
char	*ft_strndup(char *str, unsigned int n);

//exe_pipe_tools.c
int		put_fds(t_vars *vars, int i, int *ii, int out_type);
int		create_pipes(t_vars *vars);
int		set_fds(t_vars *vars, int i);
int		set_input(t_vars *vars, int i);
int		set_output(t_vars *vars, int i);

//heredoc.c
void	start_heredoc(char *stopper, int fd);
int		search_heredoc(t_vars *vars, int i, int *ii);

//lenght_tools.c
int		ft_str_len(const char *str);
int		dolvar_len(char *token);
int		token_len(char *token, t_vars *vars, char sep);
int		inquoteslen(int i, char *input, char c);
void	var_len(t_indexes *i, char *in);

//lexer_tools.c
int		check_meta(char *in, int i);
int		inquotes(int i, char *input, char c, t_vars *vars);
int		count_nb_tokens(char *input, t_vars *vars, t_indexes ind);

//lexer.c
int		lexer(char *input, t_vars *vars);
void	tokenizer(t_vars *vars, t_indexes *ind, char *input);
void	new_token(char *in, t_vars *vars, t_indexes i);

//main.c
void	set_prompt(t_vars *vars);

//list_tools.c
t_list	*ft_lst_new(void *content, void *name);
void	ft_lst_add_front(t_list **lst, t_list *new1);
char	*ft_str_dup(const char *str);

//quit_clean.c
void	clean_command(t_vars *vars, char *input);
void	quit_terminal(t_vars *vars, t_list *variables, char *input);

//signals.c
void	sig_handler_children(int sig);
void	sig_handler_parent(int sig);
void	sig_handler(int sig);
void	init_signals(int children);

//splits.c
char	*subsubsplit(t_vars *vars, int *j);
char	**subsplit(t_vars *vars, int *j, int index);
void	split_cmds(t_vars *vars);

//splits2.c
int		ft_is_quote(t_indexes i, char *token, char sep);
void	ft_retrieve_commands(t_vars *vars, char **cmnd, int i, int ind);
char	*split_tokens(char *token, t_vars *vars, t_indexes i, int len);

//tools.c
char	*ft_getenv(t_vars *vars);
char	*tolower_str(char *str, int capital);
int		ft_strichr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*get_cmd(char *input);

//var.c
void	export_to_env(t_vars *vars, char *input, char *variable);
int		add_variable(t_vars *vars, char *variable);
char	*get_variable(t_vars *vars, char *variable);
char	*use_variable(t_vars *vars, char *var);
int		check_var(t_vars *vars, int i);

#endif
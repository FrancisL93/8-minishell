/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:59:00 by anhebert          #+#    #+#             */
/*   Updated: 2022/09/15 09:40:39 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
add_history,
printf, malloc, free, write, access,
open, read, close,
fork, wait, waitpid, wait3, wait4,
signal, sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir,
stat, lstat, fstat, unlink, execve,
dup, dup2, pipe,
opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv,
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
Notes
1- Vérifier si pas exit / ctrl-d
	exit le programme
2- Couper le input en section
	< redirect input
	> redirect output
	<< should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history
	<< should redirect output in append mode.
3- on pipe une fois
4- executer la commande
	utiliser variables environnement ($ARG, $PATH, etc)
	Rediriger le output si | (Pipe)
	Être réceptif si recoît (ctrl-c / ctrl-d / ctrl-\)
5- Générer un historique de commandes (Arranger le décalage)

*Modifier export, recréer réalloc pour ENV

*/
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "stdio.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "errno.h"

# define CLEAN "\e[1;1H\e[2J"
# define BLUE "\e[1;34m"
# define IN 0
# define OUT 1

typedef struct s_cmds
{
	char				*cmd; // commande isolée pour execve ex(ls)
	char				**cmds; // commande avec ses arguments ex(ls -l)
	int					index;
	pid_t				pid;
}					t_cmds;

typedef struct s_token
{
	char	**tokens;
}	t_token;

typedef struct s_vars
{
	char	***args; // ensemble des commandes séparées par un pipe, incluant les redirections et files
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
void	export(t_vars *vars);

//built_in_tools.c
void	set_pwd(t_vars *vars, char *oldpath);
int		ftstrnstr(char *current_path, char *cmd);
char	*ftstrjoin(char *cmd, char *current_path);
char	*ftstrtrim(char	*current_path);
char	*check_path(char *cmd, char *current_path);

//exe.c
void	execute(t_vars *vars);

//exe_tools.c
char	*get_path(char *cmnd, char **envp);
char	*ft_strndup(char *str, unsigned int n);

//lexer.c
void	lexer(char *input, t_vars *vars);

//pipe_tools.c
void	split_cmds(t_vars *vars);

//quit_clean.c
void	quit_terminal(t_vars *vars, t_list *variables);
void	clean_command(t_vars *vars, char *input);
void 	free_redir(t_vars *vars, int i, int ii);

//tools.c
char	*tolower_str(char *str, int capital);
void	set_prompt(t_vars *vars);
int		ft_strichr(const char *s, int c);
char	*get_cmd(char *input);

//var.c
void	export_to_env(t_vars *vars, char *variable);
void	add_variable(t_vars *vars, char *variable);
char	*get_variable(t_vars *vars, char *variable);
char	*use_variable(t_vars *vars, char *var);
t_list	*ft_lst_new(void *content, void *name);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:58:40 by flahoud           #+#    #+#             */
/*   Updated: 2022/08/31 16:49:28 by flahoud          ###   ########.fr       */
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


extern char	**environ;

 typedef struct s_varlist
{
	char			*var;
	char			*content;
	struct s_varlist	*next;
}					t_varlist;

typedef struct s_token
{
	char	**tokens;
}	t_token;

typedef struct s_vars
{
	char	*prompt;
	char	*cmd;
	int		heredoc_fd;
	int		fdin;
	int		fdout;
	int		built_in;
	int		pipe;
	int		nb_tokens;
	int		token_len;
	t_token	token;
	t_list	variables;
}t_vars;

typedef struct s_indexes
{
	int	i;
	int	ii;
	int	j;
	int	jj;
}	t_indexes;

//built_in.c
void	cd(char *input);
void	print_env(void);
void	print_path(void);
void	echo(char *str);
void	export(t_vars *vars, char *input);

//built_in_tools.c
void	set_pwd(char *oldpath);
int		ftstrnstr(char *current_path, char *cmd);
char	*ftstrjoin(char *cmd, char *current_path);
char	*ftstrtrim(char	*current_path);
char	*check_path(char *cmd, char *current_path);

//exe.c
int		execute(t_vars *vars, char *input);
void	execute_cmd(char *input);

//exe_pipes.c
void	execute_pipes(t_vars *vars, char *input);

//exe_tools.c
char	*get_path(char *cmnd, char **envp);
int		ft_strichr(const char *s, int c);

//heredoc.c
char	*find_variable(t_vars *vars, char *input);
void	add_variable(t_vars *vars, char *input);

//lexer
void	lexer(char *input, t_vars *vars);

//main.c

//parsing.c
void	filter_input(t_vars *vars, char *input);

//tools.c
char	*tolower_str(char *str);
char	*get_cmd(char *input);
void	set_prompt(t_vars *vars);
void	realloc_env(int	new);

//quit.c
void	quit(t_vars *vars);

#endif
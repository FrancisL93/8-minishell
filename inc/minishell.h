/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:58:40 by flahoud           #+#    #+#             */
/*   Updated: 2022/08/29 12:51:12 by flahoud          ###   ########.fr       */
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
5- Générer un historique de commandes
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

typedef struct s_vars
{
	char	**envp;
	char	*prompt;
}t_vars;

//cd utils
void	set_pwd(char *oldpath);
int		ftstrnstr(char *current_path, char *cmd);
char	*ftstrjoin(char *cmd, char *current_path);
char	*ftstrtrim(char	*current_path);
char	*check_path(char *cmd, char *current_path);

//built_in
void	cd(char *input);
void	print_env(void);
void	print_path(void);
void	echo(char *str);

//exe.c
int		execute_input(t_vars *vars, char *input);

//lexer
void	lexer(char *input);

//main.c
char	*get_cmd(char *input);

#endif
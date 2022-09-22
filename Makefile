# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 10:55:27 by flahoud           #+#    #+#              #
#    Updated: 2022/09/22 10:59:46 by anhebert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c \
		src/built_in_tools.c src/built_in_tools2.c src/built_in.c src/built_in2.c \
		src/check_builtins.c \
		src/exe_tools.c src/exe.c \
		src/heredoc.c \
		src/lenght_tools.c src/lexer.c src/list_tools.c \
		src/quit_clean.c \
		src/signals.c src/splits.c src/splits2.c \
		src/tools.c \
		src/var.c

LIBFT = inc/libft
LIBFTA = inc/libft/libft.a
LIBREADLINE = inc/readline/libhistory.a inc/readline/libreadline.a

S = src/
O = obj/
I = inc/

CC = gcc
CFLAGS += -Wall -Wextra -Werror
CFLAGS += -I$I
LDFLAGS +=

OBJ = $(SRC:$S%=$O%.o)

RM = /bin/rm -f
RMDIR = /bin/rm -rf

all: $(NAME)


$O: #Create obj directory
	@mkdir $@
	@echo "\033[0;32mGenerating objects...\033[0m"

$(OBJ): | $O

$(OBJ): $O%.o: $S% #Build objectfs $< take the name on the right of ":", $@ take the name on the left of ":"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFTA): #Compile Liibft
	@echo "\033[0;32mCompiling libft...\033[0m"
	@make -C $(LIBFT)
	@make clean -C $(LIBFT)
	@echo "\033[0;32mLibft compiled!\033[0m"
	
$(NAME): $(LIBFTA) $(OBJ) #Libft will compile only once, use "make libft" to recompile
	@echo "\033[0;32mCompiling minishell...\033[0m"
	@$(CC) $(CFLAGS) $(LIBREADLINE) $(LIBFTA) $(OBJ) -o $(NAME) -lreadline -lcurses
	@echo "\033[0;32mMinishell compiled! Execute as: ./minishell\033[0m"
	
cleanobj: #Delete .o files in obj directory
	@$(RM) $(wildcard $(OBJ))

cleanobjdir: cleanobj #Delete obj directory
	@$(RMDIR) $O

clean: cleanobjdir #Delete obj directory and content
	@echo "\033[0;31mObjects deleted!\033[0m"

fclean: clean #Delete objects and executable
	@$(RM) $(NAME)
	@echo "\033[0;31mExecutable deleted!\033[0m"

fclean-all: fclean #Delete objects, executable, and libft
	@make fclean -C $(LIBFT)
	@echo "\033[0;31mLibft deleted!\033[0m"

re: fclean #Delete all and rebuild executable
	@make

libft: #Rebuild libft
	@echo "\033[0;31mLibft deleted!\033[0m"
	@make re -C $(LIBFT)
	@make clean -C $(LIBFT)
	@echo "\033[0;32mLibft recompiled!\033[0m"

debug: $(LIBFTA) $(OBJ) #Compile for debugger
	@echo "\033[0;32mCompiling minishell...\033[0m"
	@$(CC) $(CFLAGS) $(LIBREADLINE) $(LIBFTA) $(OBJ) -o $(NAME) -lreadline -lcurses
	@echo "\033[0;32mMinishell compiled! Execute as: ./minishell\033[0m"
	
exe: $(NAME) #Execute program
	./$(NAME)

exe-leak: $(NAME)
	valgrind --suppressions=".ignore_read".txt --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

gitupdate:
	printf '\nEnter pull or fetch to update from Origin: ' && read PULLFETCH && \
	printf '\nEnter Branch Name (Press Enter For All Branches): ' && \
	read BRANCH && git $$PULLFETCH origin $$BRANCH

gitadd: fclean #Clean repo before adding files to git
	git add *

gitcommit: gitadd #Commit modifications locally before push, takes user input for commit's name
	@printf '\nEnter Commit Name: '
	@read COMMIT && git commit -m $$COMMIT

gitpush: gitcommit #Push commit to remote repo
	@printf '\nEnter Branch To Push (Press Enter For ALL): '
	@read PUSH && git push origin $$PUSH && git push gitmini $$PUSH

gitmerge: #Merge specific branch to current branch
	@printf '\nEnter Branch To Merge With (Press Enter To Merge ALL): '
	@read MERGE && git merge $$MERGE && git merge $$MERGE

gitfetch: #Fetch to update branches without merging with local repo
	@printf '\nEnter Branch To Fetch (Press Enter For All Branches): '
	@read FETCH && git fetch origin $$FETCH
	
gitpull: #Pull to overwrite local data if repo is different
	@printf '\nEnter Branch To Pull (Press Enter For All Branches): '
	@read PULL && git pull origin $$FETCH

list: 	#Show all make rules
	@grep '^[^#[:space:]].*:' Makefile

.PHONY: all clean fclean re

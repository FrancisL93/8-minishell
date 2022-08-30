# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 10:55:27 by flahoud           #+#    #+#              #
#    Updated: 2022/08/30 13:23:12 by flahoud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c src/exe.c src/exe_tools.c \
	src/lexer.c src/parsing.c \
	src/built_in.c src/built_in_tools.c \
	src/tools.c

LIBFTA = inc/libft.a

S = src/
O = obj/
I = inc/

CC = gcc
CFLAGS += -Wall -Wextra -Werror -g
CFLAGS += -I$I
LDFLAGS +=

OBJ = $(SRC:$S%=$O%.o)

RM = /bin/rm -f
RMDIR = /bin/rm -rf

all: $(NAME)

$O:
	@mkdir $@
	@echo "\033[0;32mGenerating objects...\033[0m"

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "\033[0;32mCompiling minishell...\033[0m"
	@$(CC) -lreadline $(LIBFTA) $(OBJ) -o $(NAME)
	@echo "\033[0;32mMinishell compiled! Execute as: ./minishell\033[0m"
	
cleanobj:
	@$(RM) $(wildcard $(OBJ))

cleanobjdir: cleanobj
	@$(RMDIR) $O

clean: cleanobjdir
	@echo "\033[0;31mObjects deleted!\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[0;31mExecutable deleted!\033[0m"

re: fclean
	@make

exe: $(NAME)
	./$(NAME)

#Clean repo before adding files
gitadd: fclean
	git add *

#Commit modifications locally before push, takes user input for commit's name
gitcommit: gitadd
	@printf 'Enter Commit Name: '
	@read COMMIT && git commit -m $$COMMIT

#Push commit to remote repo
gitpush: gitcommit
	@printf 'Enter Branch To Push (Press Enter For ALL): '
	@read PUSH && git push origin $$PUSH && git push gitmini $$PUSH

.PHONY: all clean fclean re

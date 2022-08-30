# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flahoud <flahoud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/28 10:55:27 by flahoud           #+#    #+#              #
#    Updated: 2022/08/30 13:08:02 by flahoud          ###   ########.fr        #
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
	@echo "\033[0;32mGenerating objects..."

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) -lreadline $(LIBFTA) $(OBJ) -o $(NAME)
	@echo "\033[0;32mMinishell compiled! Execute as: ./minishell"
	
cleanobj:
	@$(RM) $(wildcard $(OBJ))

cleanobjdir: cleanobj
	@$(RMDIR) $O

clean: cleanobjdir
	@echo "\033[0;31mObjects deleted!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Executable deleted!"

re: fclean
	@make

exe: $(NAME)
	./$(NAME)

#Clean repo before adding files
gitadd: fclean
	git add *

#Commit modifications locally before push, takes user input for commit's name

gitcommit: $(COMMIT) gitadd
	read -r -p "Enter Commit Name: " COMMIT;
	git commit -m $COMMIT

.PHONY: all clean fclean re

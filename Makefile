# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 10:52:00 by vgrankul          #+#    #+#              #
#    Updated: 2020/02/27 16:08:26 by vgrankul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = minishell.c word_splitting.c create_command_list.c environ.c parameter_expansion.c tilde_expansion.c handle_command_list.c create_command_struct.c expansions.c exec.c functions.c ./builtins/builtins.c ./builtins/setenv.c ./builtins/unsetenv.c ./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/exit.c
OBJECTS = minishell.o word_splitting.o create_command_list.o environ.o parameter_expansion.o tilde_expansion.o handle_command_list.o create_command_struct.o expansion.o exec.o functions.o builtins.o setenv.o unsetenv.o cd.o echo.o env.o exit.o
INC = ./

all: $(NAME)
	
$(NAME):
	make -C ./libft
	gcc -Wextra -Werror -Wall -I $(INC) $(SRC) -L libft/ -lft -o $(NAME) -ggdb3

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

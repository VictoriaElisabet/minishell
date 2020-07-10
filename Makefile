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
SRC = minishell.c split_commands.c create_command_list.c parameter_expansion.c tilde_expansion.c argv_list.c
OBJECTS = minishell.o split_commands.o create_command_list.o parameter_expansion.o tilde_expansion.o argv_list.o
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

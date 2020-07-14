/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:24:05 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/27 13:01:07 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./libft/libft.h"

# define BUF_SIZE 32

# define PIPE_OP		1
# define OR_OP			2
# define PIPE_AMP_OP	4
# define AMP_OP 		8
# define AND_OP 		16
# define S_COL_OP		32		
# define NEWLINE		64

//int     count_words(char *command);
//int     count_wordlength(char *command);

typedef struct	s_env
{
	char *name;
	char *value;

}				t_env;

typedef struct	s_command
{
	char		**variables;
	char		**argv;
	char		*ctrl_op;

}				t_command;


int     str_chr(char *str, int c);

char    **split_commands(char *command);
char   	**create_command_list(char *prt_str);
char    **create_argv_list(char **argv, char **words);
char	*tilde_expansion(char *word, t_env **env);
char	*parameter_expansion(char *word, t_env **env);

void	destroy_arr(char **arr);
void    word_expansion(char **words, t_env **env);

t_command    **create_command_struct_list(char *prt_str, t_env **env);

#endif

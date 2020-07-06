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

# define OR_OP			1
# define AMP_OP 		2
# define AND_OP 		4
# define S_COL_OP		8
# define PIPE_OP		16
# define PIPE_AMP_OP	32
//int     count_words(char *command);
//int     count_wordlength(char *command);

typedef struct	s_env
{
	char *name;
	char *value;

}				t_env;

typedef struct	s_command
{
	char		**argv;
	int			ctrl_op;
}				t_command;

char    **split_commands(char *command);
char    **create_command_list(char *prt_str);
void	parameter_expansion(char **words, t_env **env);

#endif

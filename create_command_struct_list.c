/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_struct_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			count_vars(char **list)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while(list[i] != NULL)
	{
		if (str_chr(list[i], '=') == 1)
			count++;
		i++;
	}
	return (count);
}

int			count_list(char **list)
{
	int i;

	i = 0;
	while (list[i] != NULL)
		i++;
	return (i);
}

void		add_variables(char **words, t_command *command, int vars)
{
	int i;

	i = 0;
	if((command->variables = (char**)malloc(vars *sizeof(char*) + 1)))
	{
		while (words[i] != NULL && vars > 0)
		{
			command->variables[i] = ft_strdup(words[i]);
			i++;
			vars--;
		}
	}
	command->variables[i] = NULL;
}

void		add_argv(char **words, t_command *command, int start, int argc)
{
	int i;
	int j;

	i = start;
	j = 0;
	if ((command->argv = (char**)malloc(argc * sizeof(char*) + 1)))
	{
		while (words[i] != NULL && argc > 0)
		{
			command->argv[j] = ft_strdup(words[i]);
			i++;
			j++;
			argc--;
		}
	}
	command->argv[j] = NULL;
}

t_command   *fill_command_struct(t_command *command, char **words)
{
	int			argc;
	int			vars;
	int			word_nbr;

	word_nbr = count_list(words);
	vars = count_vars(words);
	argc = word_nbr - vars - 1;
	add_variables(words, command, vars);
	add_argv(words, command, vars, argc);
	if(!(command->ctrl_op = ft_strdup(words[word_nbr - 1])))
		command->ctrl_op = NULL;
	return(command);
}

t_command   **create_command_struct_list(char *prt_str, t_env **env)
{
	char		**command_list;
	char		**words;
	t_command	**commands;
	int     	comm_nbr;
	int			i;

	i = 0;
	command_list = create_command_list(prt_str);
	comm_nbr = count_list(command_list);
	if ((commands = (t_command**)malloc(comm_nbr *sizeof(t_command*) + 1)) != NULL)
	{
		while (command_list[i] != NULL)
		{
			if((words = split_commands(command_list[i])))
			{
				word_expansion(words, env);
				if((commands[i] = (t_command*)malloc(sizeof(t_command))))
				{
					//tilde_expansion(words, env);
					//parameter_expansion(words, env);
					commands[i] = fill_command_struct(commands[i], words);
				}
			}
			destroy_arr(words);
			i++;
		}
	}
	destroy_arr(command_list);
	commands[i] = NULL;
	return (commands);
}


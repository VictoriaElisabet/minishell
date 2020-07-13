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

int			count_list(char **command_list)
{
	int i;

	i = 0;
	while (command_list[i] != NULL)
		i++;
	return (i);
}

t_command   *fill_command_struct(t_command *command, char **words)
{
	int			argc;
	int			i;
	int			j;

	i = 0;
	j = 0;
	argc = count_list(words);
	command = (t_command*)malloc(sizeof(t_command));
	while(words[i] != NULL)
	{
		if (str_chr(words[i], '=') == 1)
			argc--;
		else
		{
			if (argc == 1)
				command->ctrl_op = ft_strdup(words[i]);
			else if (argc > 1)
			{
				if (!(command->argv))
					command->argv = (char**)malloc((argc - 1) * sizeof(char*) + 1);
				command->argv[j] = (char*)malloc(ft_strlen(words[i]) * sizeof(char) + 1);
				command->argv[j] = ft_strdup(words[i]);
				j++;
			}
			argc--;
		}
		i++;
	}
	command->argv[j] = NULL;
	return(command);
}

t_command   **create_command_struct_list(char *prt_str)
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
				commands[i] = fill_command_struct(commands[i], words);
			i++;
		}
	}
	commands[i] = NULL;
	return (commands);
}


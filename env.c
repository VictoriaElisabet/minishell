/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *set_value(char *argv)
{
	int i;
	char *value;

	i = 0;
	while(argv[i] != '\0' && argv[i] != '=')
		i++;
	value = ft_strsub(argv, i + 1, ft_strlen(argv) - (i + 1));
	return(value);
}

char    *set_name(char *argv)
{
	int i;
	char *name;

	i = 0;
	while(argv[i] != '\0' && argv[i] != '=')
		i++;
	name = ft_strsub(argv, 0, i);
	return(name);
}

void    print_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}
   
char    *new_command(char *command)
{
	char    *comm_str;
	int     i;

	i = 0;
	while ((command[i] == ' ' || command[i] == '\t') && command[i] != '\0')
		i++;
	comm_str = ft_strsub(command, i + 3, ft_strlen(command) - 1);
	return (comm_str);
}

int     ft_env(t_command *command, char ***env)
{
	int i;
	char *name;
	char *value;
	int     status;
	char    *comm_str;
	t_command **commands;

	//ska enfast ändra för env i denna funk
	status = 0;
	if (command->argc == 1)
		print_env(*env);
	else
	{
		i = 1;
		while (command->argv[i] != NULL && (str_chr(command->argv[i], '=') == 1))
		{
			name = set_name(command->argv[i]);
			value = set_value(command->argv[i]);
			ft_setenv(2, name, value, env);
			free(name);
			free(value);
			i++;
		}
		if(command->argv[i] != NULL)
		{
			comm_str = new_command(command->command);
			commands = create_command_struct_list(comm_str, *env);
			if (commands != NULL)
			{
				status = exec_commands(commands, env);
				destroy_commands(commands);
			}
			free(comm_str);
		}
		else
			print_env(*env);
	}
	return (status);
}
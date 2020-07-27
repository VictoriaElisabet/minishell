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

char	*set_value(char *argv)
{
	int		i;
	char	*value;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	value = ft_strsub(argv, i + 1, ft_strlen(argv) - (i + 1));
	return (value);
}

char	*set_name(char *argv)
{
	int		i;
	char	*name;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	name = ft_strsub(argv, 0, i);
	return (name);
}

void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

char	*new_command(char **argv, char *ctrl_op, int i)
{
	char	*arg;
	char	*tmp;
	char	*command;

	command = ft_strnew(1);
	while (argv[i] != NULL)
	{
		arg = ft_strjoin(argv[i], " ");
		tmp = ft_strjoin(command, arg);
		free(arg);
		free(command);
		command = tmp;
		i++;
	}
	arg = ft_strjoin(ctrl_op, " ");
	tmp = ft_strjoin(command, arg);
	free(arg);
	free(command);
	command = tmp;
	return (command);
}

int		ft_env(t_command *command, char **env)
{
	char	**tmp;
	char	*name;
	char	*value;
	int		i;
	int		status;
	char	*comm;
	char	**command_list;

	status = 0;
	tmp = copy_env(env);
	if (command->argc == 1)
		print_env(env);
	else
	{
		i = 1;
		while (command->argv[i] != NULL && (str_chr(command->argv[i], '=') == 1))
		{
			name = set_name(command->argv[i]);
			value = set_value(command->argv[i]);
			ft_setenv(2, name, value, &tmp);
			free(name);
			free(value);
			i++;
		}
		if (command->argv[i] != NULL)
		{
			if ((comm = new_command(command->argv, command->ctrl_op, i)))
			{
				if ((command_list = create_command_list(comm)))
					status = handle_command_list(command_list, &tmp);
			}
			free(comm);
			destroy_arr(command_list);
		}
		else
			print_env(tmp);
	}
	destroy_arr(tmp);
	return (status);
}

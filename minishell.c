/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void	destroy_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	destroy_command(t_command *command)
{
	destroy_arr(command->variables);
	destroy_arr(command->argv);
	free(command->command);
	free(command->ctrl_op);
	free(command);
}

char    *read_prompt(char *prompt)
{
	int     ret;
	char     ch[2];
	char    *prt_str;
	char    *tmp;

	prt_str = NULL;
	ft_printf("%s", prompt);
	while((ret = read(0, &ch, 1)) > 0)
	{   
		ch[ret] = '\0';
		if (prt_str == NULL)
			if(!(prt_str = ft_strnew(0)))
			{
				ft_printf("Malloc failed");
				exit(EXIT_FAILURE);
			}
		if ((int)ch[0] == EOF || ch[0] == '\n')
		{
			if(!(tmp = ft_strjoin(prt_str, ch)))
			{
				ft_printf("Malloc failed");
				exit(EXIT_FAILURE);
			}
			free(prt_str);
			prt_str = tmp;
			return (prt_str);
		}
		if(!(tmp = ft_strjoin(prt_str, ch)))
		{
			ft_printf("Malloc failed");
			exit(EXIT_FAILURE);
		}
		free(prt_str);
		prt_str = tmp;
	}
	if (ret < 0)
	{
		//ist för exit borde det bara vara return?
		ft_printf("Read failed");
		exit(EXIT_FAILURE);	
	}
	return (prt_str);
}

int main()
{
	char    *prt_str;
	char	   **env;
	char	**command_list;
	int		status;


	// ifall env failar då?
	status = 0;
	env = copy_env(environ);
	int t = 0;
	while(t < 1)
	{
		prt_str = read_prompt("$> ");
		if (prt_str != NULL)
		{
			//commands = create_command_struct_list(prt_str, env);
			command_list = create_command_list(prt_str);
			if (command_list != NULL)
			{
				handle_command_list(command_list, &env);
				destroy_arr(command_list);
				//status = exec_commands(commands, &env);
				//destroy_commands(commands);
			}
			free(prt_str);
		}
	/*	int i = 0;
		while(env[i] != NULL)
		{
			ft_printf("%s\n", env[i]);
			i++;
		}*/
		t++;
	}
	destroy_arr(env);
	return (status);
}
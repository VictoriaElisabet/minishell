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

void	destroy_commands(t_command **commands)
{
	int i;

	i = 0;
	while(commands[i] != NULL)
	{
		destroy_arr(commands[i]->variables);
		destroy_arr(commands[i]->argv);
		free(commands[i]->command);
		free(commands[i]->ctrl_op);
		free(commands[i]);
		i++;
	}
	free(commands);
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
	t_command **commands;
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
			commands = create_command_struct_list(prt_str, env);
			if (commands != NULL)
			{
				status = exec_commands(commands, &env);
				destroy_commands(commands);
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
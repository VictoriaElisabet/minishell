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

void	destroy_env(t_env **env)
{
	int i;

	i = 0;
	while(env[i] != NULL)
	{
		free(env[i]->name);
		free(env[i]->value);
		free(env[i]);
		i++;
	}
	free(env);
}

void	destroy_commands(t_command **commands)
{
	int i;

	i = 0;
	while(commands[i] != NULL)
	{
		destroy_arr(commands[i]->variables);
		destroy_arr(commands[i]->argv);
		free(commands[i]->ctrl_op);
		free(commands[i]);
		i++;
	}
	free(commands);
}

int     count_env_var(char **environ)
{
	int i;

	i = 0;
	while(environ[i] != NULL)
	{
		i++;
	}
	return (i);
}

t_env    **copy_env(char **environ)
{
	int i;
	int j;
	t_env **env;

	i = 0;
	j = 0;
	env = (t_env**)malloc(count_env_var(environ) * sizeof(t_env*) + 1);
	while(environ[i] != NULL)
	{
		env[i] = (t_env*)malloc(sizeof(t_env));
		if (ft_strncmp(environ[i],"SHELL=", 6) == 0)
		{
			//borde kanske vara pwd
			env[i]->name = ft_strdup("SHELL");
			env[i]->value = ft_strdup("/home/vgrankul/projects/minishell/minishell");
		}
		else
		{
			j = 0;
			while (environ[i][j] != '=')
				j++;	
			env[i]->name = ft_strsub(environ[i], 0, j);
			env[i]->value = ft_strsub(&environ[i][j + 1], 0, ft_strlen((&environ[i][j + 1])));	
		} 
		i++;
	}
	env[i] = NULL;
	return(env);
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
	t_env   **env;
	t_command **commands;


	// ifall env failar då?
	env = copy_env(environ);
	int t = 0;
	while(t < 2)
	{
		prt_str = read_prompt("$> ");
		if (prt_str != NULL)
		{
			commands = create_command_struct_list(prt_str, env);
			if (commands != NULL)
			{
				exec_commands(commands, env);
				destroy_commands(commands);
			}
			free(prt_str);
		}
		int i = 0;
		while(env[i] != NULL)
		{
			ft_printf("%s %s\n", env[i]->name, env[i]->value);
			i++;
		}
		t++;
	}
	destroy_env(env);
	return (EXIT_SUCCESS);
}
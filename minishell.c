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

t_env    **copy_env(char **environ, t_env **env)
{
	int i;
	int j;

	i = 0;
	j = 0;
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
	//char    **commands;
	//char    **words;
	//int     i;
	t_env   **env;
	//t_command	**commands;
	//char 	**argv;
	t_command **commands;

	//commands = NULL;
	env = (t_env**)malloc(count_env_var(environ) * sizeof(t_env*) + 1);
	copy_env(environ, env);
	int t = 0;
	while(t < 2)
	{
		prt_str = read_prompt("Enter info: ");
		ft_printf("prompt_str %s\n", prt_str);
		//ska vara en egen loop med cond status, så att det stannar när status är fel
		if (prt_str != NULL)
		{
			int i = 0;
			int j = 0;
			int k = 0;
			commands = create_command_struct_list(prt_str, env);
			while (commands[i] != NULL)
			{
				ft_printf("comm = %d\n", i);
				j = 0;
				while(commands[i]->variables[j] != NULL)
				{
					ft_printf("va %s\n", commands[i]->variables[j]);
					j++;
				}
				k = 0;
				while(commands[i]->argv[k] != NULL)
				{
					ft_printf("argv %s\n", commands[i]->argv[k]);
					k++;
				}
				ft_printf("ctrl %s\n", commands[i]->ctrl_op);
				
				i++;

			}
			ft_unsetenv(commands[0]->argc, commands[0]->argv, &env);
				i = 0;
				while (env[i] != NULL)
				{
					ft_printf("env %s %s\n", env[i]->name, env[i]->value);
					i++;
				}
			/*i = 0;
				while (env[i] != NULL)
			{
				ft_printf("env %s %s\n", env[i]->name, env[i]->value);
				i++;
			}*/
			/*commands = create_command_list(prt_str);
			i = 0;
			while(commands[i] != NULL)
			{
				words = split_commands(commands[i], comms);
				int j = 0;
				while(words[j] != NULL)
				{
					ft_printf("%d word %s\n", j, words[j]);
					j++;
				}
				tilde_expansion(words, env);
				parameter_expansion(words, env);
				j = 0;
				while(words[j] != NULL)
				{
					ft_printf("%d word %s\n", j, words[j]);
					j++;
				}
				argv = create_argv_list(argv, words);
				j = 0;
				while(argv[j] != NULL)
				{
					ft_printf("argv %d argv %s\n", j, argv[j]);
					j++;
				}
				destroy_arr(words);
				//ft_printf("%d\n", count_words(commands[i]));
				//execute comm
				//free argv
				i++;*/
			}
			free(prt_str);
			destroy_commands(commands);
			//destroy_arr(commands);
			//destroy_arr(words);
			
		//}
		t++;
	}
	destroy_env(env);
	return (EXIT_SUCCESS);
    //int fd;
    //fd = open(stdin, O_RDONLY);
    
    //printf("%d \n %d", getpid(), getppid());
}
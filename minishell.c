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
	ft_printf("i %d\n", i);
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
		if ((int)ch[0] == EOF || ch[0] == '\n')
			return (prt_str);
		if (prt_str == NULL)
			if(!(prt_str = ft_strnew(0)))
			{
				ft_printf("Malloc failed");
				exit(EXIT_FAILURE);
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
	char    **commands;
	char    **words;
	int     i;
	t_env   **env;

	env = NULL;
	env = copy_env(environ, env);
	/*i = 0;
	while(env[i] != NULL)
	{
		ft_printf("%s \n%s\n", env[i]->name, env[i]->value);
		i++;
	}*/
	while(1)
	{
		prt_str = read_prompt("Enter info: ");
		ft_printf("prompt_str %s\n", prt_str);
		//ska vara en egen loop med cond status, så att det stannar när status är fel
		if (prt_str != NULL)
		{
			commands = create_command_list(prt_str);
			i = 0;
			while(commands[i] != NULL)
			{
				words = split_commands(commands[i]);
				int j = 0;
				while(words[j] != NULL)
				{
					ft_printf("%d word %s\n", j, words[j]);
					j++;
				}
				parameter_expansion(words, env);
				j = 0;
				while(words[j] != NULL)
				{
					ft_printf("%d word %s\n", j, words[j]);
					j++;
				}
				//ft_printf("%d\n", count_words(commands[i]));
				//execute comm
				//free argv
				i++;
			}
			free(prt_str);
			free(commands);
		}
	}
	return (EXIT_SUCCESS);
    //int fd;
    //fd = open(stdin, O_RDONLY);
    
    //printf("%d \n %d", getpid(), getppid());
}
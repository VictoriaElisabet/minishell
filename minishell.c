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

int     count_ctrl_op(char *prt_str)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while(prt_str[i] != '\0')
	{
		if(prt_str[i] == '"' || prt_str[i] == '\'')
		{
			i++;
			while(prt_str[i] != '"' && prt_str[i] != '\'' && prt_str[i] != '\0')
				i++;
		}
		if (prt_str[i + 1] == '\0' && prt_str[i] != ';' && prt_str[i] != '|' && prt_str[i] != '&')
			count++;
		if (prt_str[i] == '|' || prt_str[i] == '&' || prt_str[i] == ';')
		{
			if (prt_str[i + 1] == '|' || prt_str[i + 1] == '&')
				i++;
			count++;
		}
		i++;        
	}
	return (count);
}

int     count_commlength(char *prt_str)
{
	int i;

	i = 0;
	while(prt_str[i] != '\0')
	{
		if(prt_str[i] == '"' || prt_str[i] == '\'')
		{
			i++;
			while(prt_str[i] != '"' && prt_str[i] != '\'' && prt_str[i] != '\0')
				i++;
		}
		if (prt_str[i] == '|' || prt_str[i] == '&' || prt_str[i] == ';')
		{
			i++;
			if (prt_str[i] == '|' || prt_str[i] == '&')
				i++;
			break ;
		}
		i++;
	}
	return (i);
}

char    **create_command_list(char *prt_str)
{
	char    **commands;
	int     i;
	int     j;
	int     comms;

	j = 0;
	i = 0;
	comms = count_ctrl_op(prt_str);
	if(!(commands = (char**)malloc(comms * sizeof(char*) + 1)))
	{
		ft_printf("Malloc failed");
		exit(EXIT_FAILURE);
	}
	while (j < comms)
	{
		if(!(commands[j] = ft_strsub(&prt_str[i], 0, count_commlength(&prt_str[i]))))
		{
			ft_printf("Malloc failed");
			exit(EXIT_FAILURE);
		}
		i = i + count_commlength(&prt_str[i]);
		j++;
	}
	commands[j] = NULL;
	return (commands);
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

char    **copy_env(char **environ, char **env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	env = (char**)malloc(count_env_var(environ) * sizeof(char*) + 1);
	while(environ[i] != NULL)
	{
		if (ft_strncmp(environ[i],"SHELL=", 6) == 0)
			//borde kanske vara pwd
			env[i] = ft_strdup("SHELL=/home/vgrankul/projects/minishell/minishell");

		else
		{
			j = 0;
			env[i] = (char*)malloc(ft_strlen(environ[i]) * sizeof(char) + 1);
			while(environ[i][j] != '\0')
			{
				env[i][j] = environ[i][j];	
				j++;
			}
			env[i][j] = '\0';
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
	char    **env;

	env = NULL;
	env = copy_env(environ, env);
	i = 0;
	while(env[i] != NULL)
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
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
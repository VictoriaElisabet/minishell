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

int	ctrl_function(char *ctrl_op, int status)
{
	ft_printf("op and status %s %d\n", ctrl_op, status);
	if ((ft_strcmp(ctrl_op, "||") == 0) && status != 0)
		return (1);
	if ((ft_strcmp(ctrl_op, "&&") == 0) && status == 0)
		return (1);
	if (ft_strcmp(ctrl_op, ";") == 0 || ft_strcmp(ctrl_op, "\n") == 0)
		return (1);
	return (0);
}

char 	*search_path(char *name, char *path)
{
	DIR *dir;
	struct dirent *dirent;
	char	*file_path;
	char	*tmp;

	if ((dir = opendir(path)))
	{
		while ((dirent = readdir(dir)) != NULL)
		{
			if (ft_strcmp(dirent->d_name, name) == 0)
			{
				tmp = ft_strjoin (path, "/");
				file_path = ft_strjoin(tmp, name);
				free (tmp);
				return (file_path);
			}
		}
		//if closedir fails
		closedir(dir);
	}
	return (NULL);
}

char	*find_executable(char *name, t_env **env)
{
	char *path;
	char **paths;
	char *file_path;
	int i;

	i = 0;
	if ((path = check_env(env, "PATH")))
	{
		if ((paths = ft_strsplit(path, ':')))
		{
			while (paths[i] != NULL)
			{
				if ((file_path = search_path(name, paths[i])) != NULL)
					return (file_path);
				i++;
			}
		}
	}
	return (NULL);
}

int	exec_commands(t_command **commands, t_env **env)
{
	int status;
	int i;
	pid_t pid;
	char	*file_path;

	i = 0;
	status = 0;
	pid = 0;
	while(commands[i] != NULL)
	{
		if (ctrl_function(commands[i]->ctrl_op, status) == 1)
		{
			
			//if status = builtin (commands[i]);
			//else
			pid = fork();
			//if (pid == -1)
				//fork failed
			if (pid == 0)
			{
				// if command[i] har slashes, kolla om ok med stat och ifall det är run the program med exec.
				//annars sök efter i path. check stat att executable
				//chlid
				file_path = find_executable(commands[i]->argv[0], env);
				if ((execve(file_path, commands[i]->argv, environ)) == -1)
					ft_printf("Execution failed");
				//free file path;
			}
			else
			{
				pid = waitpid(pid, &status, 0);
				ft_printf("statis %d\n", status);
				
			}

		}
		i++;

	}
	return (status);
}

int main()
{
	char    *prt_str;
	t_env   **env;
	t_command **commands;

	env = (t_env**)malloc(count_env_var(environ) * sizeof(t_env*) + 1);
	copy_env(environ, env);
	int t = 0;
	while(t < 2)
	{
		prt_str = read_prompt("Enter info: ");
		//ska vara en egen loop med cond status, så att det stannar när status är fel
		if (prt_str != NULL)
			commands = create_command_struct_list(prt_str, env);
		if (commands != NULL)
			exec_commands(commands, env);
		free(prt_str);
		destroy_commands(commands);
		t++;
	}
	destroy_env(env);
	return (EXIT_SUCCESS);
}
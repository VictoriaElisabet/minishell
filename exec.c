/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

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

int	ctrl_function(char *ctrl_op, int status)
{
	if ((ft_strcmp(ctrl_op, "||") == 0) && status != 0)
		return (1);
	if ((ft_strcmp(ctrl_op, "&&") == 0) && status == 0)
		return (1);
	if (ft_strcmp(ctrl_op, ";") == 0 || ft_strcmp(ctrl_op, "\n") == 0)
		return (1);
	return (0);
}

int run_command(t_command *command, t_env **env)
{
	pid_t	pid;
	char	*file_path;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		//fork failde;
	}
	if (pid == 0)
	{
		// if command[i] har slashes, kolla om ok med stat och ifall det är run the program med exec.
		//annars sök efter i path. check stat att executable !!!
		//chlid
		// change environ to my own env, need to be a char **arr
		if (str_chr(command->argv[0], '/') == 1)
			file_path = ft_strdup(command->argv[0]);
		else
			file_path = find_executable(command->argv[0], env);
		if (!(file_path))
		{
			ft_printf("%s: command not found\n", command->argv[0]);
			return (127);
		}
		if ((execve(file_path, command->argv, environ)) == -1)
			ft_printf("Execution failed");
		//free file path;
	}
	else
	{
		pid = waitpid(pid, &status, 0);			
	}
	return (status);
}

int	exec_commands(t_command **commands, t_env **env)
{
	int status;
	int i;

	i = 0;
	status = 0;
	//skapa en char **env anv t_env
	while(commands[i] != NULL)
	{	
		if (commands[i]->argc != 0)
		{
			if (is_builtin(commands[i]) == 1)
				status = run_builtin(commands[i], env);
			else
				status = run_command(commands[i], env);
			if (ctrl_function(commands[i]->ctrl_op, status) != 1)
			{
				if (commands[i + 1] != NULL)
					i++;
			}
		}
		i++;
	}
	return (status);
}
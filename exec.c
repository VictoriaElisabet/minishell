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
				if((tmp = ft_strjoin (path, "/")))
				{
					if((file_path = ft_strjoin(tmp, name)))
					{
						free (tmp);
						return (file_path);
					}
				}
			}
		}
		closedir(dir);
	}
	return (NULL);
}

char	*find_executable(char *name, char **env)
{
	char *path;
	char **paths;
	char *file_path;
	int i;

	i = 0;
	if ((path = get_env_value("PATH", env)))
	{
		if ((paths = ft_strsplit(path, ':')))
		{
			while (paths[i] != NULL)
			{
				if ((file_path = search_path(name, paths[i])) != NULL)
				{
					destroy_arr(paths);
					return (file_path);
				}
				i++;
			}
		}
	}
	destroy_arr(paths);
	return (NULL);
}

int		print_exec_error(t_command *command, int status)
{
	if(WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 11)
			ft_printf("Segmentation fault\n");
	}
	else if (status == 125)
	{
		ft_printf("%s: command not found\n", command->argv[0]);
		return (125);
	}
	else if (status == 126)
	{
		ft_printf("%s: command not an executable\n", command->argv[0]);
		return (126);
	}
	else if (status == 127)
	{
		ft_printf("%s: No such file or directory\n", command->argv[0]);
		return (127);
	}
	return (EXIT_FAILURE);
}

int run_command(t_command *command, char **env)
{
	pid_t	pid;
	char	*file_path;
	int 	status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (print_exec_error(command, EXIT_FAILURE));
	if (pid == 0)
	{
		if (str_chr(command->argv[0], '/') == 1)
			file_path = ft_strdup(command->argv[0]);
		else
			file_path = find_executable(command->argv[0], env);
		if (!(file_path))
			return (print_exec_error(command, 127));
		if (access(file_path, F_OK) != -1)
		{
			if(access(file_path, X_OK))
				return (print_exec_error(command, 126));
			if ((execve(file_path, command->argv, env)) == -1)
				return (print_exec_error(command, 125));
		}
		else
			return (print_exec_error(command, 127));
		free(file_path);
	}
	else
		pid = waitpid(pid, &status, 0);
	return ((print_exec_error(command, status)));
}

int	exec_command(t_command *command, char ***env)
{
	int status;

	status = 0;
	if (command->argc != 0)
	{
		if (is_builtin(command) == 1)
			status = run_builtin(command, env, status);
		else
			status = run_command(command, *env);
	}
	return (status);
}
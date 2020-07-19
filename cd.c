/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_last(char *path)
{
	int len;
	char *new_path;

	len = ft_strlen(path);
	while(path[len] != '/' && len > 0)
	{
		len--;
	}
	new_path = ft_strsub(path, 0, len);
	ft_printf("new %s\n", new_path);
	return (new_path);
}

char    *correct_path(char *path)
{
	int i;
	int j;
	char	*tmp;
	char	*dir;
	char	*new_path;
	int start;

	i = 0;
	tmp = ft_strnew(1);
	new_path = ft_strnew(1);
	while (path[i] != '\0')
	{
		if (path[i] == '/')
		{
			j = 1;
			start = i;
			while (path[i + 1] != '/' && path[i + 1] != '\0')
			{
				i++;
				j++;
			}
			dir = ft_strsub(path, start, j);
			ft_printf("tmp %s\n", dir);
			if (ft_strcmp(dir, "/..") == 0)
			{
				ft_printf("hii");
				
				tmp = remove_last(new_path);
				free(new_path);
				new_path = tmp;
			}
			else
			{
			tmp = ft_strjoin(new_path, dir);
			free(new_path);
			new_path = tmp;
			free(dir);
			}

		}		
		i++;
	}
	ft_printf("PATH %s\n", new_path);
	return (new_path);
}


int ft_cd (int argc, char **argv, t_env ***env)
{
	char *HOME;
	char *PWD;
	char *OLDPWD;
	char *path;
	char *tmp;

	//ifall inte hittas och dessa är NULL?
	HOME = check_env(*env, "HOME");
	PWD = check_env(*env, "PWD");
	OLDPWD = check_env(*env, "OLDPWD");
	
	if (argc > 2)
	{
		ft_printf("Too many arguments");
		return (-1);
	}
	if (argv[1] == NULL)
	{
		ft_printf("%s\n", PWD);
		ft_setenv(2, "OLDPWD", PWD, env);
		ft_setenv(2, "PWD", HOME, env);

	}
	else if (argv[1][0] == '-')
	{
		ft_setenv(argc, "OLDPWD", PWD, env);
		ft_setenv(argc, "PWD", OLDPWD, env);
	}
	else if(argv[1][0] == '/')
		correct_path(argv[1]);
	else
	{
		tmp = ft_strjoin(PWD, "/");
		path = ft_strjoin(tmp, argv[1]);
		free (tmp);
		correct_path(path);
		//ft_setenv(argc, "OLDPWD", PWD, &env);
		//ft_setenv(argc, "PWD", path, &env);
	}
	return (0);
}
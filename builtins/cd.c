/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		change_wdir(char *path, char **argv, char ***env)
{
	char	*old_pwd;
	char	*pwd;

	if(!(old_pwd = getcwd(NULL, 0)))
		return (EXIT_FAILURE);
	if(chdir(path) == -1)
	{
		ft_printf("%s: %s: No such file or directory\n", argv[0], path);
		return (EXIT_FAILURE);
	}
	if (!(pwd = getcwd(NULL, 0)))
		return (EXIT_FAILURE);
	if (ft_setenv(2, "PWD", pwd, env) != 0)
		return (EXIT_FAILURE);
	if (ft_setenv(2, "OLDPWD", old_pwd, env) != 0)
		return (EXIT_FAILURE);
	free(pwd);
	free(old_pwd);
	return (0);
}

int ft_cd (int argc, char **argv, char ***env)
{
	char	*path;

	if (argc > 2)
	{
		ft_printf("%s: too many arguments\n", argv[0]);
		return (2);
	}
	else if (argv[1] == NULL)
	{
		if (!(path = get_env_value("HOME", *env)))
		{
			ft_printf("%s: HOME not set\n", argv[0]);
			return (EXIT_FAILURE);
		}
	}
	else if (argv[1][0] == '-')
	{
		if (!(path = get_env_value("OLDPWD", *env)))
		{
			ft_printf("%s: OLDPWD not set\n", argv[0]);
			return (EXIT_FAILURE);
		}
		ft_printf("%s\n", path);
	}
	else
		path = argv[1];
	return (change_wdir(path, argv, env));
}
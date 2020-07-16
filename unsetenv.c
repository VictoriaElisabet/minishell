/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_env(t_env **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
        i++;
    return (i);
}

t_env    **remove_env(const char *name, t_env **env)
{
	int     i;
	int		j;
	t_env   **new;
	int		count;

	i = 0;
	j = 0;
	count = count_env(env) - 1;
	if((new = (t_env**)malloc((count * sizeof(t_env*) + 1))))
	{
		while (j < count)
		{
			if (ft_strcmp (name, env[i]->name) == 0)
				i++;
			if(!(new[j] = (t_env*)malloc(sizeof(t_env))))
				return (NULL);
			if(!(new[j]->name = ft_strdup(env[i]->name)) || !(new[j]->value = ft_strdup(env[i]->value)))
				return (NULL);
			i++;
			j++;
		}
	}
	new[j] = NULL;
	return (new);
}

int     find_env(const char *name, t_env **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        if (ft_strcmp(name, env[i]->name) == 0)
            return (0);
        i++;
    }
    return (i);
}

int     ft_unsetenv(int argc, char **argv, t_env ***env)
{
	t_env **tmp;

	if (argc != 2)
	{
		ft_printf("Incorrect number of arguments\n");
		return (-1);
	}
	if (argv[1] == NULL || ft_strlen(argv[1]) == 0 || str_chr(argv[1], '=') == 1)
		return (-1);
	if (find_env(argv[1], *env) == 0)
	{
		if(!(tmp = remove_env(argv[1], *env)))
			return (-1);
		destroy_env(*env);
		*env = tmp;
	}
	return (0);
}
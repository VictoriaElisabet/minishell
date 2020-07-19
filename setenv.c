/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env    **add_env(const char *name, const char *value, t_env **env, int count)
{
    int     i;
    t_env   **new;

    i = 0;
    if((new = (t_env**)malloc(count * sizeof(t_env*) + 1)))
    {
        while (i < count)
        {
            if(!(new[i] = (t_env*)malloc(sizeof(t_env))))
                return (NULL);
            if (env[i] == NULL)
            {
                if(!(new[i]->name = ft_strdup(name)) || !(new[i]->value = ft_strdup(value)))
                    return (NULL);
            }
            else
            {
                if(!(new[i]->name = ft_strdup(env[i]->name)) || !(new[i]->value = ft_strdup(env[i]->value)))
                    return (NULL);
            }
            i++;
        }
    }
    new[i] = NULL;
    return (new);
}

int     set_env(const char *name, const char *value, t_env **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        if (ft_strcmp(name, env[i]->name) == 0)
        {
            free(env[i]->value);
            if(!(env[i]->value = ft_strdup(value)))
                return (-1);
            return (0);
        }
        i++;
    }
    return (i);
}

int     ft_setenv(int argc, char *name, char *value, t_env ***env)
{
    int		index;
    t_env   **tmp;
    char	*val;

    if (argc < 2 || argc > 3)
    {
        ft_printf("Incorrect number of arguments\n");
        return (-1);
    }
    if (name == NULL || ft_strlen(name) == 0 || str_chr(name, '=') == 1)
		return (-1);
	value != NULL ? (val = value) : (val = "\0");
    if ((index = set_env(name, val, *env)) != 0)
    {
        if(index == -1 || !(tmp = add_env(name, val, *env, index + 1)))
            return (-1);
        destroy_env(*env);
        *env = tmp;
    }
    return (0);
}
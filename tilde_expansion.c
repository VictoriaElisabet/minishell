/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env(t_env **env, char *name)
{
	int i;

	i = 0;
	while(env[i] != NULL)
	{
		if (ft_strcmp(name, env[i]->name) == 0)
			return (env[i]->value);
		i++;
	}
	return (NULL);
}

char	*get_value(char *t_prefix, t_env **env)
{
	char *value;

	if ((ft_strcmp(t_prefix, "~/") == 0 || ft_strcmp(t_prefix, "~") == 0) && (value = check_env(env, "HOME")) != NULL)
		return(value);
	else if (ft_strcmp(&t_prefix[1], (value = check_env(env, "USER"))) == 0)
	{
		if ((value = check_env(env, "HOME")) != NULL)
			return (value);
	}
	else if (ft_strcmp(t_prefix, "~+") == 0 && (value = check_env(env, "PWD")) != NULL)
		return(value);
	else if (ft_strcmp(t_prefix, "~-") == 0 && (value = check_env(env, "OLDPWD")) != NULL)
		return(value);
	return(NULL);
}

char	*tilde_expansion(char *word, t_env **env)
{
    int     i;
    char    *t_prefix;
    char    *value;
    char    *result;
    char    *tmp;

    i = 0;
    value = NULL;
    result = word;
    if (word[0] == '~')
    {
        while(word[i] != '/' && word[i] != '\0')
				i++;
			if((t_prefix = ft_strsub(word, 0, i)) != NULL && (value = get_value(t_prefix, env)) != NULL)
			{
				if((tmp = ft_strjoin(value, &word[i])) != NULL)
				{
					free(word);
					result = tmp;
				}
			}
			free(t_prefix);
    }
    return (result);
}
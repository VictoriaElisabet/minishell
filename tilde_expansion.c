/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
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

void	tilde_expansion(char **words, t_env **env)
{
	int i;
	int j;
	char *t_prefix;
	char *tmp;
	char *value;
	
	j = 0;
	i = 0;
	value = NULL;
	while(words[i] != NULL)
	{
		if (words[i][0] == '~')
		{
			j = 0;
			while(words[i][j] != '"' && words[i][j] != '\'' && words[i][j] != '/' && words[i][j] != '\0')
				j++;
			if((t_prefix = ft_strsub(words[i], 0, j)) != NULL && (value = get_value(t_prefix, env)) != NULL)
			{
				if((tmp = ft_strjoin(value, &words[i][j])) != NULL)
				{
					free(words[i]);
					words[i] = tmp;
				}
			}
			free (t_prefix);
		}
		i++;
	}
}
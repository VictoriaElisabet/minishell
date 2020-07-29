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

char	*get_name(char *param)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	len = ft_strlen(param);
	if (param == NULL)
		return ("\0");
	while (ft_isalnum(param[i]) != 1 && param[i] != '\0' && len-- > 0)
	{
		if (param[i] == '{')
			len--;
		i++;
	}
	name = ft_strsub(&param[i], 0, len);
	return (name);
}

int		get_param(char *word, char **param)
{
	int		i;

	i = 1;
	if (word[i] == '{')
	{
		while (word[i] != '}')
			i++;
		i++;
	}
	else
	{
		while (word[i] != '$' && word[i] != '"' && word[i] != '\0' &&
		word[i] != '}')
			i++;
	}
	*param = ft_strsub(word, 0, i);
	return (i);
}

char	*expand_param(char *param, char **env)
{
	char	*value;
	int		i;
	char	*name;

	i = 0;
	name = get_name(param);
	while (env[i] != NULL)
	{
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0)
		{
			value = get_env_value(name, env);
			free(name);
			return (value);
		}
		i++;
	}
	free(name);
	return ("\0");
}

char	*parameter_expansion(char *word, char **env)
{
	int		i;
	char	*value;
	char	*param;
	char	*temp;
	char	*tmp;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			temp = ft_strsub(word, 0, i);
			i = i + get_param(&word[i], &param);
			value = expand_param(param, env);
			tmp = ft_strjoin(temp, value);
			free(temp);
			free(param);
			temp = ft_strjoin(tmp, ft_strsub(word, i, strlen(&word[i])));
			free(word);
			word = temp;
		}
		i++;
	}
	return (word);
}

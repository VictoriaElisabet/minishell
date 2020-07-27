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

char	*replace_var(char *word, int j, char **env)
{
	int		i;
	int		k;
	char	*name;
	char	*value;
	char	*begin;

	i = 0;
	k = 0;
	while (word[i] != '$' && word[i] != '\0' && j > 0)
	{
		i++;
		j--;
	}
	if (!(begin = ft_strsub(word, 0, i)))
		begin = ft_strcpy(ft_strnew(1), "\0");
	while (ft_isalnum(word[i + k]) != 1 && word[i + k] != '\0' && j-- > 0)
		k++;
	if ((name = ft_strsub(&word[i + k], 0, j)) != NULL)
	{
		i = 0;
		while (env[i] != NULL)
		{
			if (ft_strncmp(name, env[i], ft_strlen(name)) == 0)
			{
				if ((value = ft_strjoin(begin, get_env_value(name, env))) != NULL)
				{
					free(begin);
					free(name);
					return (value);
				}
			}
			i++;
		}
	}
	free(name);
	free(begin);
	return (ft_strcpy(ft_strnew(1), "\0"));
}

char	*parameter_expansion(char *word, char **env)
{
	int		i;
	char	*replaced;
	char	*tmp;
	int		braces;

	i = 0;
	braces = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			if (word[i + 1] == '{')
				braces = 1;
			while (word[i + 1] != '\0' && word[i + 1] != '}' && word[i + 1] != '$' && word[i + 1] != '"')
				i++;
			if ((replaced = replace_var(word, i + 1, env)))
			{
				if (braces == 1)
					i++;
				if ((tmp = ft_strjoin(replaced, &word[i + 1])) != NULL)
				{
					free(word);
					word = tmp;
				}
				free(replaced);
			}
		}
		i++;
	}
	return (word);
}

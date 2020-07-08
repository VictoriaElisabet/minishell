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

char	*replace_var(char *word, int j, t_env **env)
{
	int		i;
	int		k;
	char	*name;
	char	*value;
	char	*begin;

	i = 0;
	k = 0;
	while(word[i] != '$' && word[i] != '\0' && j > 0)
	{
		i++;
		j--;
	}
	if(!(begin = ft_strsub(word, 0, i)))
		begin = ft_strnew(1);
	while(ft_isalnum(word[i + k]) != 1 && word[i + k] != '\0' && j-- > 0)
		k++;
	name = ft_strsub(&word[i + k], 0, j);
	i = 0;
	while(env[i] != NULL)
	{
		if(ft_strcmp(name, env[i]->name) == 0)
		{
			value = ft_strjoin(begin, env[i]->value);
			free(begin);
			return (value);
		}
		i++;
	}
	return("\0");
}

void	parameter_expansion(char **words, t_env **env)
{
	int		i;
	int 	j;
	char	*replaced;
	char	*tmp;

	i = 0;
	while (words[i] != 0)
	{
		j = 0;
		while(words[i][j] != '\0')
		{
			if(words[i][j] == '\'')
			{
				j++;
				while(words[i][j] != '\'' && words[i][j] != '\0')
					j++;
			}
			if (words[i][j] == '$')
			{
				j++;
				while (words[i][j] != '\'' && words[i][j] != '\0' && words[i][j] != '}' && words[i][j] != '$' &&words[i][j] != '"')
					j++;
				replaced = replace_var(words[i], j, env);
				if(words[i][j] == '}')
					j++;
				tmp = ft_strjoin(replaced, &words[i][j]);
				free(words[i]);
				words[i] = tmp;
			}
			j++;
		}
		i++;			
	}
}
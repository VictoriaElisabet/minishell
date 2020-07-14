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
	if((name = ft_strsub(&word[i + k], 0, j)) != NULL)
	{
		i = 0;
		while(env[i] != NULL)
		{
			if(ft_strcmp(name, env[i]->name) == 0)
			{
				if((value = ft_strjoin(begin, env[i]->value)) != NULL)
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
	return(ft_strnew(1));
}

char	*parameter_expansion(char *word, t_env **env)
{
	int		i;
	char	*replaced;
	char	*tmp;
    char    *result;

	i = 0;
    result = word;
	while (word[i] != '\0')
	{
	    if (word[i] == '$')
		{
				i++;
				while (word[i] != '\0' && word[i] != '}' && word[i] != '$' && word[i] != '"')
					i++;
                ft_printf("cee %c\n", word[i]);
				if ((replaced = replace_var(word, i, env)))
				{
					if(word[i] == '}')
						i++;
					if((tmp = ft_strjoin(replaced, &word[i])) != NULL)
					{
						free(result);
						result = tmp;
					}
					free(replaced);
				}
		}
		i++;
	}
    return (result);		
}
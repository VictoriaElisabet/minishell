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

char	*find_var(char *replace, t_env **env)
{
	int		i;
	int		j;
	int		k;
	char	*begin;
	char	*replaced;

	i = 0;
	j = 0;
	k = 0;
	while(replace[k] != '$' && replace[k] != '\0')
		k++;
	begin = ft_strsub(&replace[0], 0, k);
	while(ft_isalnum(replace[j + k]) != 1 && replace[j + k] != '\0')
		j++;
	while(env[i] != NULL && replace[j + k] != '\0')
	{
		if(ft_strcmp(&replace[j + k], env[i]->name) == 0)
		{
			replaced = ft_strjoin(begin, env[i]->value);
			free(begin);
			return (replaced);
		}
		i++;
	}
	replaced = ft_strjoin(begin, "\0");
	free(begin);
	return(replaced);
}

void	parameter_expansion(char **words, t_env **env)
{
	int		i;
	int 	j;
	char	*replace;
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
				replace = ft_strsub(&words[i][0], 0, j);
				ft_printf("%s %d\n", &words[i][j], j);
				replaced = find_var(replace, env);
				tmp = ft_strjoin(replaced, &words[i][j]);
				ft_printf("repl %s repld %s temp %s\n", replace, replaced, tmp);
				free (words[i]);
				words[i] = tmp;
				free (replace);
				//free (replaced);
				//j = j + ft_strlen(&words[i][j]);
				ft_printf("char %c %d\n", words[i][j], j);

			}
			j++;
		}
		i++;			
	}
}
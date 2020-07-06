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

char	*find_var(char *str, t_env **env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	//if(str[1] == '\0')
	//	return (NULL);
	while(ft_isalnum(str[j]) != 1)
		j++;
	while(env[i] != NULL && str[j] != '\0')
	{
		if(ft_strncmp(&str[j], env[i]->name, ft_strlen(&str[j])) == 0)
		{
			
			return (env[i]->value);
		}
		i++;
	}
	return(ft_strnew(1));
}

void	parameter_expansion(char **words, t_env **env)
{
	int		i;
	int 	j;
	int 	k;
	char	*value;
	char	*param;
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
				while (words[i][j] != '\'' && words[i][j] != '\0')
					j++;
			}
			if(words[i][j] == '$')
			{
				k = 1;
				//j++;
				//if (words[i][j + k] == '{')
				//	j++;
				while (words[i][j + k] != '\'' && words[i][j + k] != '\0' && words[i][j + k] != '}' && words[i][j + k] != '$')
					k++;
				if(!(param = ft_strsub(&words[i][j], 0, k)))
				{
					ft_printf("hi");
					param = ft_strnew(1);
				}
				ft_printf("pa %s\n", param);
				//print_env(env);
				value = find_var(param, env);
				tmp = ft_strjoin(value, &words[i][k]);
				free(words[i]);
				words[i] = tmp;
				j = j + k;
			}
			j++;
		}
		i++;
	}
}
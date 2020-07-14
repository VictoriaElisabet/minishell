/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     str_chr(char *str, int c)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if(str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

void    word_expansion(char **words, t_env **env)
{
    int i;

    i = 0;
    while (words[i] != NULL)
    {
        if (str_chr(words[i], '\'') != 1)
        {
            if (str_chr(words[i], '"') != 1)
            {
                words[i] = tilde_expansion(words[i], env);
            }
            words[i] = parameter_expansion(words[i], env);
        }
        i++;
    }
}
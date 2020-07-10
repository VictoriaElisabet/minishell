/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_list.c                                        :+:      :+:    :+:   */
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

char    **create_argv_list(char **argv, char **words)
{
    while(*words != NULL && (str_chr(*words, '=') == 1))
        words++;
    argv = words;
    return (argv);
}
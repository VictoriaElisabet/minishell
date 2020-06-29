/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_words(char *command)
{
    int i;
	int count;

	i = 0;
	count = 0;
    while ((command[i] == ' ' || command[i] == '\t') && command[i] != '\0')
    {
        i++;
    }
	while (command[i] != '\0')
	{
        if (command[i] == '"' || command[i] == '\'')
        {
            count++;
            ft_printf("hii");
            while (command[i + 1] != '"' && command[i + 1] != '\'' && command[i + 1] != '\0')
            {
                i++;
            }
            i++;
        }
        if (command[i + 1] == '\0' && command[i] != '|' && command[i] != '&' && command[i] != '"' && command[i] != '\'')
        {
            ft_printf("hiid");
            count++;
        }
		if (command[i] == ' ' && command[i + 1] != ' ' && command[i + 1] != '\0')
			count++;
        if (command[i] == '\t' && command[i + 1] != '\t' && command[i + 1] != '\0')
			count++;
        if (command[i] == '|' || command[i] == '&')
        {
            if (command[i + 1] == '|' || command[i + 1] == '&')
                i++;
            count++;
        }
		i++;
	}
	return (count);
}

/*int     count_commlength(char *prt_str)
{
    int i;

    i = 0;
    while(prt_str[i] != '\0')
    {
        if (prt_str[i] == '|' || prt_str[i] == '&' || prt_str[i] == ';')
        {
            i++;
            if (prt_str[i] == '|' || prt_str[i] == '&')
                i++;
            break ;
        }
        i++;
    }
    return (i);
}

char    **split_commands(char *command)
{
    char    **words;
    int     i;
    int     j;
    int     words_nbr;

    j = 0;
    i = 0;
    words_nbr = count_words(command);
    if(!(commands = (char**)malloc(comms * sizeof(char*) + 1)))
	{
		ft_printf("Malloc failed");
		exit(EXIT_FAILURE);
	}
    while (j < comms)
    {
        if(!(commands[j] = ft_strsub(&prt_str[i], 0, count_commlength(&prt_str[i]))))
		{
			ft_printf("Malloc failed");
			exit(EXIT_FAILURE);
		}
        i = i + count_commlength(&prt_str[i]);
        j++;

    }
    commands[j] = NULL;
    return (commands);
}*/
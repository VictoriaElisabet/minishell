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
	ft_printf("comman %s\n", command);
    while (command[i] != '\0')
    {
        if (command[i] != ' ' && command[i] != '\t' && command[i] != '|' && command[i] != '&' && command[i] != ';')
        {
            count++;
            while(command[i] != ' ' && command[i] != '\t' && command[i] != '|' && command[i] != '&' && command[i] != ';' && command[i] != '\0')
            {
                if(command[i] == '"' || command[i] == '\'')
                {
                    i++;
                    while (command[i] != '"' && command[i] != '\'' && command[i] != '\0')
                        i++;
                }
                i++;
            }
        }
        if (command[i] == '|' || command[i] == '&' || command[i] == ';')
        {
            if (command[i + 1] == '|' || command[i + 1] == '&')
                i++;
            count++;
        }
        i++;
    }
	return (count);
}

/*int     count_wordlength(char *command)
{
    int i;
	int j;

    i = 0;
	j = 0;
    while(command[i] != '\0')
    {
		if (command[i] != ' ' && command[i] != '\t' && command[i] != '|' && command[i] != '&')
        {
            while(command[i] != ' ' && command[i] != '\t' && command[i] != '|' && command[i] != '&' && command[i] != '\0')
            {
                if(command[i] == '"' || command[i] == '\'')
                {
                    i++;
                    while (command[i] != '"' && command[i] != '\'' && command[i] != '\0')
                        i++;
                }
                j++;
				i++;
            }
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
    if(!(commands = (char**)malloc(words_nbr * sizeof(char*) + 1)))
	{
		ft_printf("Malloc failed");
		exit(EXIT_FAILURE);
	}
    while (j < words_nbr)
    {
        if(!(words[j] = ft_strsub(&command[i], 0, count_commlength(&command[i]))))
		{
			ft_printf("Malloc failed");
			exit(EXIT_FAILURE);
		}
        i = i + count_commlength(&command[i]);
        j++;

    }
    words[j] = NULL;
    return (words);
}*/
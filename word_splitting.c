/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
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
    while (command[i] != '\0')
    {
        if (command[i] != ' ' && command[i] != '\t' && command[i] != '|' && command[i] != '&' && command[i] != ';' && command[i] != '\n')
        {
            count++;
            while(command[i] != ' ' && command[i] != '\t' && command[i] != '|' && command[i] != '&' && command[i] != ';' && command[i] != '\n' && command[i] != '\0')
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
        if (command[i] == '|' || command[i] == '&' || command[i] == ';' || command[i] == '\n')
        {
            if (command[i + 1] == '|' || command[i + 1] == '&')
                i++;
            count++;
        }
        i++;
    }
	return (count);
}

int     count_wordlength(char *command)
{
    int i;

    i = 0;
	if (command[0] == '|' || command[0] == '&' || command[0] == ';' || command[0] == '\n')
	{
		i++;
		if (command[i] == '|' || command[i] == '&')
        	i++;
		return (i);
	}
	while(command[i] != '|' && command[i] != '&' && command[i] != ';' && command[i] != ' ' && command[i] != '\t' && command[i] != '\n' && command[i] != '\0')
	{
		if(command[i] == '"' || command[i] == '\'')
        {
            i++;
            while (command[i] != '"' && command[i] != '\'' && command[i] != '\0')
                i++;
        }
		i++;
	}
    return (i);
}

char    **word_splitting(char *command)
{
    char    **words;
    int     i;
    int     j;
    int     words_nbr;

    j = 0;
    i = 0;
    words_nbr = count_words(command);
    if(!(words = (char**)malloc(words_nbr * sizeof(char*) + 1)))
        return (NULL);
    while (j < words_nbr)
    {
		while ((command[i] == ' ' || command[i] == '\t') && command[i] != '\0')
			i++;
        if(!(words[j] = ft_strsub(&command[i], 0, count_wordlength(&command[i]))))
            return (NULL);
        i = i + count_wordlength(&command[i]);
        j++;
    }
    words[j] = NULL;
    return (words);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filearr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

char    *read_prompt(char *prompt)
{
    /*int ret;
    char buf[BUF_SIZE + 1];

    ft_printf("%s", prompt);
    while ((ret = read(0, buf, BUF_SIZE)) > 0)
    {
        if(ft_strchr(buf, EOF) || ft_strchr(buf, '\n'))
            break ;
    }*/
    int     ret;
    char     ch[2];
    char    *prompt_string;
    char    *tmp;

    prompt_string = NULL;    
    ft_printf("%s", prompt);
    while((ret = read(0, &ch, 1)) > 0)
    {
        ch[ret] = '\0';
        if ((int)ch[0] == EOF || ch[0] == '\n')
        {

            break ;
        }
        if (prompt_string == NULL)
            prompt_string = ft_strnew(0);
        tmp = ft_strjoin(prompt_string, ch);
        free(prompt_string);
        prompt_string = tmp;
    }
    return (prompt_string);
}

int main()
{
    char *prompt_string;
    while(1)
    {
        prompt_string = read_prompt("Enter info: ");
        ft_printf("strin = %s\n", prompt_string);
    }
    //int fd;
    //fd = open(stdin, O_RDONLY);
    
    //printf("%d \n %d", getpid(), getppid());
}
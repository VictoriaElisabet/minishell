/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
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
int     count_ctrl_op(char *prt_str)
{
    int count;
    int i;

    i = 0;
    count = 0;
    while(prt_str[i] != '\0')
    {
        if (prt_str[i] == '|' || prt_str[i] == '&' || prt_str[i] == ';')
        {
            if (prt_str[i + 1] == '|' || prt_str[i + 1] == '&')
                i++;
            count++;
        }
        i++;        
    }
    ft_printf("count %d\n", count);
    return (count);
}

int     count_commlength(char *prt_str)
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
    ft_printf("i = %d", i);
    return (i);
}

char    **split_commands(char *prt_str)
{
    char    **commands;
    int     i;
    int     j;

    j = 0;
    i = 0;
    commands = (char**)malloc(count_ctrl_op(prt_str) * sizeof(char*) + 1);
    while (prt_str[i] != '\0')
    {
        commands[j] = ft_strsub(&prt_str[i], 0, count_commlength(&prt_str[i]));
        ft_printf("c %s\n", commands[j]);
        j++;
        i = i + count_commlength(&prt_str[i]);

    }
    commands[j] = NULL;
    return (commands);
}

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
    char    *prt_str;
    char    *tmp;
   
    prt_str = NULL;
    ft_printf("%s", prompt);
    while((ret = read(0, &ch, 1)) > 0)
    {   
        ch[ret] = '\0';
        if ((int)ch[0] == EOF || ch[0] == '\n')
            return (prt_str);
        if (prt_str == NULL)
            prt_str = ft_strnew(0);
        tmp = ft_strjoin(prt_str, ch);
        free(prt_str);
        prt_str = tmp;
    }
    return (prt_str);
}

int main()
{
    char *prt_str;
    char **commands;
    int     i;

    i = 0;
    while(1)
    {
        prt_str = read_prompt("Enter info: ");
         ft_printf("prompt_str%s\n", prt_str);
       commands = split_commands(prt_str);
       
        while(commands[i] != NULL)
           ft_printf("%s\n", commands[i++]);
        

    }
    return (EXIT_SUCCESS);
    //int fd;
    //fd = open(stdin, O_RDONLY);
    
    //printf("%d \n %d", getpid(), getppid());
}
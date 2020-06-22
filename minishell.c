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

void    read_prompt(char *prompt)
{
    int ret;
    char buf[BUF_SIZE + 1];

    ft_printf("%s", prompt);
    while ((ret = read(0, buf, BUF_SIZE)) > 0)
    {
        if(ft_strchr(buf, EOF) || ft_strchr(buf, '\n'))
            break ;
    }
}

int main()
{
    while(1)
        read_prompt("Enter info: ");
    //int fd;
    //fd = open(stdin, O_RDONLY);

    //printf("%d \n %d", getpid(), getppid());
}
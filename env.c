/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *set_value(char *argv)
{
    int i;
    char *value;

    i = 0;
    while(argv[i] != '\0' && argv[i] != '=')
        i++;
    value = ft_strsub(argv, i + 1, ft_strlen(argv) - (i + 1));
    return(value);
}

char    *set_name(char *argv)
{
    int i;
    char *name;

    i = 0;
    while(argv[i] != '\0' && argv[i] != '=')
        i++;
    name = ft_strsub(argv, 0, i);
    return(name);
}

void    print_env(char **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        ft_printf("%s\n", env[i]);
        i++;
    }
}

int     ft_env(t_command *command, char ***env)
{
    int i;
    char *name;
    char *value;
    int     status;

    i = 0;
    status = 0;
    if (command->argc == 1)
        print_env(*env);
    else
    {
        while (command->variables[i] != NULL)
        {
            name = set_name(command->variables[i]);
            value = set_value(command->variables[i]);  
            ft_setenv(2, name, value, env);
            i++;
        }
        if(command->argv[i] != NULL)
        {
            status = exec_commands(&command, env);
            //free commands;
        }
    }
    return (status);
}
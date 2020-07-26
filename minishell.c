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

#include "minishell.h"

extern char **environ;

char    *read_prompt(char *prompt)
{
	int     ret;
	char     ch[2];
	char    *prt_str;
	char    *tmp;

	prt_str = NULL;
	ft_printf("%s", prompt);
	while((ret = read(0, &ch, 1)) > 0)
	{   
		ch[ret] = '\0';
		if (prt_str == NULL)
			if(!(prt_str = ft_strnew(0)))
				return (NULL);
		if ((int)ch[0] == EOF || ch[0] == '\n')
		{
			if(!(tmp = ft_strjoin(prt_str, ch)))
				return (NULL);
			free(prt_str);
			prt_str = tmp;
			return (prt_str);
		}
		if(!(tmp = ft_strjoin(prt_str, ch)))
			return (NULL);
		free(prt_str);
		prt_str = tmp;
	}
	if (ret < 0)
		return (NULL);
	return (prt_str);
}

int main()
{
	char	*prt_str;
	char	**env;
	char	**command_list;
	int		status;


	// ifall env failar då?
	status = 0;
	env = copy_env(environ);
	int t = 0;
	while(t < 1)
	{
		prt_str = read_prompt("$> ");
		if (prt_str != NULL)
		{
			command_list = create_command_list(prt_str);
			if (command_list != NULL)
			{
				handle_command_list(command_list, &env);
				destroy_arr(command_list);
			}
			free(prt_str);
		}
		t++;
	}
	destroy_arr(env);
	return (status);
}
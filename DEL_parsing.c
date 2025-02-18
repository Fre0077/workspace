/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:25:37 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/29 11:44:49 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ----------------------------------------------------------------

// char	*arg_echo(char *line)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 4;
// 	while (line[i] == ' ')
// 		i++;
// 	tmp = str_dup_till_charset(&(line[i]), "|");
// 	return (tmp);
// }

int	parse_command(char *line, char **env)
{
	char	*arg[] = {"clear", NULL};
	// char	*tmp;
	char	**args;

	if (ft_strncmp(line, "clear", 5) == 0 && ft_strchr(" ", line[5]))
	{
		if (fork() == 0)
			execve("/usr/bin/clear", arg, env);
	}
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strchr(" ", line[4]))
	{
		free(line);
		exit(0);
	}
	if (ft_strncmp(line, "echo", 4) == 0 && ft_strchr(" ", line[4]))
	{
		//fatto prima parte del aprsing per echo, penso si possa utilizzare anche per il
		// parsing generale 
		//ft_printf("%s\n", line);
		args = slice_args(line);
		int i = 0;
		while (args[i] != NULL)
			ft_printf("%s\n", args[i++]);
		free(args);
		// tmp = arg_echo(line);
		// if (tmp[0] == '-')
		// {
		// 	if (ft_strncmp(tmp, "-n", 2) == 0 && ft_strchr(" ", tmp[2]))
		// 		ft_printf("%s", &(tmp[2]));
		// 	else
		// 		ft_printf(RED "Error: " YELLOW "invalid option" END "\n");
		// }
		// else
		// 	ft_printf("%s\n", tmp);
		// free(tmp);
	}
	else
	{
		ft_printf(RED "Error: " YELLOW "command not found" END "\n");
		return (1);
	}
	return (0);
}

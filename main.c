/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:06:42 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/17 09:03:01 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

// ctrl + d -> EOF (get_next_line returns NULL) -> exit
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line;
	char	*history;

	using_history();
	init_signals();
	line = NULL;
	while (1) // !(ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{
		g_signal = 0;
		free(line);
		line = readline("\001"CYAN BOLD"\002minishell\001"RED BOLD"\002 > \001"END"\002");
		printf("%s\n", line);
		if (line == NULL)
		{
			ft_printf("\nexit");
			exit(0);
		}
		//testing...
		t_cmd	*cmds;
		cmds = parsing(line);
		(void)cmds;
		//print_cmq(cmds);
		//testing...
		//parse_command(line, env);
		history = ft_strtrim(line, "\n ");
		add_history(history);
		write_history("history.txt");
		free(history);
	}
	return (0);
}

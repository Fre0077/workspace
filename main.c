/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:06:42 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/19 16:46:04 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

// ctrl + d -> EOF (get_next_line returns NULL) -> exit
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int		i = 10;
	char	*line;
	char	*history;
	t_data	data;

	if (init_data(&data, env) == 1)
		return (1);
	using_history();
	init_signals();
	line = NULL;
	while (i--) // !(ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{
		g_signal = 0;
		free(line);
		line = readline("\001"CYAN BOLD"\002minishell\001"RED BOLD"\002 > \001"END"\002");
		if (line == NULL)
		{
			ft_printf("exit");
			exit(0);
		}
		//testing...
		data.cmds = parsing(line, &data);
		if (data.cmds != NULL)
			exec_cmd(&data);
		//testing...
		history = ft_strtrim(line, "\n ");
		add_history(history);
		write_history("history.txt");
		free(history);
	}
	free_env(data.env);
	return (0);
}

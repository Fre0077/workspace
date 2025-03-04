/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:06:42 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/04 11:24:32 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

// ctrl + d -> EOF (get_next_line returns NULL) -> exit
int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*history;
	t_data	data;

	(void)ac;
	(void)av;
	if (init_data(&data, env) == 1)
		return (1);
	using_history();
	init_signals();
	line = NULL;
	while (1)
	{
		g_signal = 0;
		free(line);
		line = readline(MINI);
		if (line == NULL)
		{
			ft_printf("exit");
			ft_exit(&data);
		}
		data.cmds = parsing(line, &data);
		printf("status: %d\n", data.status);
		if (data.status == 1)
		{
			free_cmds(data.cmds);
			data.status = 0;
			history = ft_strtrim(line, "\n ");
			add_history(history);
			write_history(HISTORY);
			free(history);
			continue ;
		}
		data.head = data.cmds;
		exec_cmd(&data);
		// if (check_status(&data) == 1)
		// 	ft_exit(&data);
		free_cmds(data.head);
		data.head = NULL;
		data.cmds = NULL;
		history = ft_strtrim(line, "\n ");
		add_history(history);
		write_history(HISTORY);
		free(history);
	}
	ft_exit(&data);
}

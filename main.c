/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:06:42 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/20 16:08:22 by alborghi         ###   ########.fr       */
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
			exit(0);
		}
		data.cmds = parsing(line, &data);
		if (data.cmds != NULL)
			exec_cmd(&data);
		history = ft_strtrim(line, "\n ");
		add_history(history);
		write_history("history.txt");
		free(history);
	}
	free_env(data.env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:06:42 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/23 18:34:34 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

// ctrl + d -> EOF (get_next_line returns NULL) -> exit
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line;
	char	*history;

	using_history();
	init_signals();
	line = NULL;
	while (1) // !(ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{
		g_signal = 0;
		free(line);
		line = readline(CYAN BOLD "minishell" RED BOLD " > " END);
		if (line == NULL)
		{
			ft_printf("\nexit");
			exit(0);
		}
		parse_command(line, env);
		history = ft_strtrim(line, "\n ");
		add_history(history);
		write_history("history.txt");
		free(history);
	}
	return (0);
}

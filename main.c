/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:06:42 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/24 12:34:34 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	ft_putdata(t_data *data)
{
	ft_printf("\ndata->env: %p\n", data->env);
	ft_printf("data->cmds: %p\n", data->cmds);
	ft_printf("data->status: %d\n", data->status);
	ft_printf("data->home: %p\n", data->home);
	ft_printf("data->pwd: %p\n", data->pwd);
	ft_printf("data->oldpwd: %p\n", data->oldpwd);
	ft_printf("data->stdin: %d\n", data->stdi);
	ft_printf("data->stdout: %d\n", data->stdo);
}

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
			// ft_putdata(&data);
			ft_exit(&data);
		}
		data.cmds = parsing(line, &data);
		data.head = data.cmds;
		// ft_printf("cmds parsed\n");
		// print_cmd(data.cmds);
		if (data.cmds != NULL)
			exec_cmd(&data);
		free_cmds(data.head);
		data.head = NULL;
		data.cmds = NULL;
		history = ft_strtrim(line, "\n ");
		add_history(history);
		write_history(HISTORY);
		free(history);
	}
	// free_env(data.env);
	ft_exit(&data);
	return (0);
}

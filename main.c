/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:06:42 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/12 16:44:52 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	check_is_folder(char *file)
{
	struct stat	buf;

	if (!file)
		return (0);
	if (stat(file, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			printf("minishell: %s: is a directory\n", file);
			return (1);
		}
	}
	return (0);
}

int	check_files(t_cmd *cmds)
{
	int		i;

	while (cmds)
	{
		if (check_is_folder(cmds->file_a) == 1
			|| check_is_folder(cmds->file_o) == 1)
		{
			return (1);
		}
		i = 0;
		while (cmds->file_i && cmds->file_i[i])
		{
			if (check_is_folder(cmds->file_i[i]) == 1)
				return (1);
			i++;
		}
		cmds = cmds->next;
	}
	return (0);
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
			printf("exit\n");
			ft_exit(&data, 0);
		}
		data.cmds = parsing(line, &data);
		if (data.cmds == NULL)
			continue ;
		// printf("-------------------------------------------\n");
		// print_cmd(data.cmds);
		// print_data(&data);
		// printf("status: %d\n", data.status);
		// printf("-------------------------------------------\n");
		if (data.status != 0)
		{
			data.status = 0;
			free_cmds(data.cmds);
			history = ft_strtrim(line, "\n ");
			add_history(history);
			write_history(HISTORY);
			free(history);
			continue ;
		}
		if (check_files(data.cmds) == 1)
		{
			free_cmds(data.cmds);
			data.status = 1;
			continue ;
		}
		if (data.cmds->cmd == NULL || data.cmds->cmd[0] == '\0')
		{
			// printf("cmds: %s\n", data.cmds->cmd);
			handle_files(data.cmds, &data);
			free_cmds(data.cmds);
			reset_std(&data);
			history = ft_strtrim(line, "\n ");
			add_history(history);
			write_history(HISTORY);
			free(history);
			continue ;
		}
		data.head = data.cmds;
		exec_cmd(&data);
		reset_std(&data);
		// if (check_status(&data) == 1)
		// 	ft_exit(&data, 1);
		free_cmds(data.head);
		data.head = NULL;
		data.cmds = NULL;
		history = ft_strtrim(line, "\n ");
		add_history(history);
		write_history(HISTORY);
		free(history);
	}
	ft_exit(&data, 1);
}

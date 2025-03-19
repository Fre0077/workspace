/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:06:42 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/18 10:43:12 by alborghi         ###   ########.fr       */
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
			ft_printe("minishell: %s: is a directory\n", file);
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
			ft_printf("exit\n");
			ft_exit(&data, data.out);
		}
		history = ft_strtrim(line, "\n ");
		add_history(history);
		write_history(HISTORY);
		free(history);
		data.cmds = parsing(line, &data);
		if (data.cmds == NULL)
		{
			data.status = 0;
			continue ;
		}
		// ft_printf("-------------------------------------------\n");
		// print_cmd(data.cmds);
		// print_data(&data);
		// ft_printf("status: %d\n", data.status);
		// ft_printf("-------------------------------------------\n");
		if (data.status != 0)
		{
			data.status = 0;
			free_cmds(data.cmds);
			continue ;
		}
		if (check_files(data.cmds) == 1)
		{
			free_cmds(data.cmds);
			data.status = 1;
			continue ;
		}
		// do_heredoc(&data);
		data.head = data.cmds;
		exec_cmd(&data);
		int status = 0;
		while (data.pids && waitpid(data.pids->n, &status, 0) >= 0)
		{
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			{
				ft_printe("Quit (core dumped)\n");
				g_signal = 0;
				break;
			}
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				data.out = WEXITSTATUS(status);
			}
			data.pids = remove_node(data.pids);
		}
		if (WIFSIGNALED(status))
			data.out = (WTERMSIG(status) + 128);
		if (WIFEXITED(status))
			data.out = (WEXITSTATUS(status));
		init_signals();
		reset_std(&data);
		free_cmds(data.head);
		close_fds(data.fds);
		data.fds = NULL;
		data.head = NULL;
		data.cmds = NULL;
	}
	ft_exit(&data, data.out);
}

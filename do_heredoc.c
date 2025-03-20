/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:51:57 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/19 17:36:06 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd)
		return (0);
	while (cmd->cmd)
	{
		if (cmd->delimiter)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	skip_heredoc(t_cmd *cmd)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (cmd->delimiter[i + 1])
	{
		line = readline("> ");
		if (!line || !line[0])
		{
			ft_printe("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", j, cmd->delimiter[i]);
			j = 1;
			i++;
			continue ;
		}
		if (ft_strncmp(line, cmd->delimiter[i], ft_strlen(cmd->delimiter[i]) + 1) == 0)
		{
			free(line);
			j = 1;
			i++;
			continue ;
		}
		free(line);
		j++;
	}
	return (0);
}

int	save_heredoc(t_cmd *cmd, int n)
{
	char	*line;
	int		i;
	int		fd;
	int		flag;
	int		j;

	cmd->here_file = ft_strjoin_free_2("tmp/.heredoc_", ft_itoa(n));
	fd = open(cmd->here_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	i = ft_char_mat_len(cmd->delimiter) - 1;
	line = NULL;
	flag = 1;
	j = 1;
	while (cmd->delimiter[i])
	{
		line = readline("> ");
		if (g_signal == 2)
		{
			close(fd);
			return (130);
		}
		if (!line || !line[0])
		{
			ft_printe("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", j, cmd->delimiter[i]);
			j = 1;
			i++;
			continue ;
		}
		if (ft_strncmp(line, cmd->delimiter[i], ft_strlen(cmd->delimiter[i]) + 1) == 0)
		{
			free(line);
			j = 1;
			i++;
			continue ;
		}
		line = ft_strtrim_free(line, "\n");
		ft_putendl_fd(line, fd);
		free(line);
		j++;
	}
	close(fd);
	return (0);
}

int	do_heredoc(t_data *data)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = data->cmds;
	while (tmp)
	{
		if (tmp->delimiter && tmp->delimiter[0])
		{
			if (skip_heredoc(tmp) == 1)
				return (1);
			if (save_heredoc(tmp, i++) == 1)
				return (1);
		}
		else
			tmp->here_file = NULL;
		tmp = tmp->next;
	}
	return (0);
}

int	read_heredoc(char *file)
{
	int		fd;
	char	*line;
	int		pipe_fd[2];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	if (pipe(pipe_fd) == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	return (0);
}
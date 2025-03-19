/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:51:57 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/19 12:48:26 by alborghi         ###   ########.fr       */
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

int	skip_heredoc(char **delimiter)
{
	char	*line;
	int		i;

	i = 0;
	while (delimiter[i])
	{
		line = readline("> ");
		if (!line)
			return (1);
		if (ft_strncmp(line, delimiter[i], ft_strlen(delimiter[i]) + 1) == 0)
		{
			free(line);
			i++;
			continue;
		}
		free(line);
	}
	return (0);
}

int	save_heredoc(char **delimiter)
{
	char	*line;
	int		i;
	int		fd;
	int		flag;

	i = 0;
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	line = NULL;
	flag = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter[i], ft_strlen(delimiter[i]) + 1) == 0)
		{
			free(line);
			break ;
		}
		line = ft_strtrim_free(line, "\n");
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (0);
}

int	do_heredoc(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	i = 0;
	j = 0;
	tmp = data->cmds;
	while (tmp)
	{
		if (tmp->delimiter && check_heredoc(tmp->next) == 1)
		{
			if (skip_heredoc(tmp->delimiter) == 1)
				return (1);
		}
		else if (tmp->delimiter)
		{
			save_heredoc(tmp->delimiter);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	read_heredoc(void)
{
	int		fd;
	char	*line;
	int		pipe_fd[2];

	fd = open(".heredoc", O_RDONLY);
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
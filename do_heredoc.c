/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:51:57 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/19 10:49:09 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(t_cmd *cmd)
{
	if (!cmd->cmd)
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
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (1);
		if (ft_strncmp(line, delimiter[i], ft_strlen(delimiter[i]) + 1) == 0)
		{
			free(line);
			break ;
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

	i = 0;
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
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
		if (tmp->delimiter && check_heredoc(data))
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

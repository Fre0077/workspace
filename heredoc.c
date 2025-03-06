/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:57:54 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/06 16:08:08 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote(char *line)
{
	char	*new;
	char	*ret;
	char	*tmp;

	new = line;
	tmp = line;
	while (*line)
	{
		if (*line == '\'')
			while (*++line && *line != '\'' && *line != '\0')
				*new++ = *line;
		else if (*line == '\"')
			while (*++line && *line != '\"' && *line != '\0')
				*new++ = *line;
		else
			*new++ = *line++;
	}
	*new = '\0';
	ret = ft_strdup(tmp);
	if (!ret)
		return (NULL);
	free(tmp);
	return (ret);
}

int	skip_useless(char **delimiter)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (delimiter[i + 1])
	{
		line = readline("> ");
		if (!line || !line[0])
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", j, delimiter[i]);
			j = 1;
			i++;
			continue ;
		}
		if (ft_strncmp(line, delimiter[i], ft_strlen(delimiter[i])) == 0)
		{
			i++;
			j = 1;
		}
		free(line);
		j++;
	}
	return (i);
}

void	read_last(char *delimiter, int fd, t_data *data, int q)
{
	char	*line;
	int		j;

	j = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", j, delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		//TODO: add dollar managment
		if (!q)
			line = dollar_manager_stupid(line, data);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		j++;
	}
}

void	handle_delimiter(char **delimiter, int doi, t_data *data)
{
	int		fd[2];
	int		i;
	int		q;

	if (!delimiter || !delimiter[0])
		return ;
	i = 0;
	while (delimiter[i])
	{
		q = ft_strchr(delimiter[i], '\'') || ft_strchr(delimiter[i], '\"');
		if (q)
			delimiter[i] = remove_quote(delimiter[i]);
		i++;
	}
	i = skip_useless(delimiter);
	pipe(fd);
	read_last(delimiter[i], fd[1], data, q);
	close(fd[1]);
	if (doi == 2 && data->cmds && data->cmds->cmd && dup2(fd[0], 0) == -1)
	{
		close(fd[0]);
		return ;
	}
	close(fd[0]);
}

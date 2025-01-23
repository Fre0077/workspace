/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:53:04 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/23 10:18:08 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_headers/get_next_line.h"

char	*till_new_line(char *buf, int fd)
{
	char	*line;
	char	*tmp;
	int		bytes;

	bytes = 1;
	line = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (!ft_strnchr(buf, '\n', ft_strlen(buf)) && bytes > 0)
	{
		bytes = read(fd, line, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), free(line), NULL);
		if (bytes != 0)
		{
			line[bytes] = '\0';
			tmp = ft_strjoin(buf, line);
			free(buf);
			buf = tmp;
		}
		else
			return (free(line), buf);
	}
	free(line);
	return (buf);
}

char	*get_new_line(char *buf, char *line)
{
	char	*tmp;

	if (!buf || !*buf)
		return (NULL);
	tmp = ft_strnchr(buf, '\n', ft_strlen(buf));
	if (tmp)
		line = ft_strndup(buf, tmp - buf + 1);
	else
		line = ft_strndup(buf, ft_strlen(buf));
	return (line);
}

char	*get_rest(char *buf)
{
	char	*tmp;
	char	*dup;

	if (!buf)
		return (NULL);
	tmp = ft_strnchr(buf, '\n', ft_strlen(buf));
	if (tmp)
	{
		dup = ft_strndup(tmp + 1, ft_strlen(tmp + 1));
		if (!dup)
			return (NULL);
		free(buf);
		return (dup);
	}
	else
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf[fd])
		buf[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	buf[fd] = till_new_line(buf[fd], fd);
	if (!buf[fd])
		return (NULL);
	line = NULL;
	line = get_new_line(buf[fd], line);
	buf[fd] = get_rest(buf[fd]);
	return (line);
}

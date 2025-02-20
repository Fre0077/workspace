/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:08:34 by fde-sant          #+#    #+#             */
/*   Updated: 2025/01/20 10:25:43 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*temp_copy(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	str[i] = '\0';
	i = -1;
	while (buffer[++i])
		str[i] = buffer[i];
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*join;
	char			*temp;
	int				read_return;

	if (buffer != NULL && check_buffer(buffer, 0) == 0)
		return (return_buffer(&buffer));
	join = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read_return = read(fd, join, BUFFER_SIZE);
	if (read_return > -1)
		join[read_return] = '\0';
	if (read_return > 0)
	{
		temp = temp_copy(buffer);
		buffer = malloc(sizeof(char) * buffer_size(temp, join));
		join_buffer(buffer, temp, join);
		if (check_buffer(buffer, read_return) == 1)
			return (get_next_line(fd));
	}
	if (read_return <= 0)
		free (join);
	return (return_buffer(&buffer));
}

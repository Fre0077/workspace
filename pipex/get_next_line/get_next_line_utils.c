/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:16:09 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/30 15:13:08 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buffer_size(char *buffer, char *join)
{
	int	buffer_len;
	int	join_len;

	buffer_len = 0;
	join_len = 0;
	if (buffer)
		while (buffer[buffer_len])
			buffer_len++;
	if (join)
		while (join[join_len])
			join_len++;
	return (buffer_len + join_len + 1);
}

int	check_buffer(char *buffer, int check_case)
{
	int	i;

	i = -1;
	if (check_case == 0)
	{
		if (!buffer)
			return (1);
		while (buffer[++i])
			if (buffer[i] == '\n')
				return (0);
	}
	else
	{
		if (check_case < BUFFER_SIZE)
			return (0);
		while (buffer[++i])
			if (buffer[i] == '\n')
				return (0);
	}
	return (1);
}

void	join_buffer(char *buffer, char *temp, char *join)
{
	int	i;
	int	k;

	if (!buffer || (!temp && !join))
		buffer = NULL;
	i = 0;
	if (temp)
		while (temp[i++])
			buffer[i - 1] = temp[i - 1];
	if (i >= 1)
		i--;
	k = 0;
	if (join)
		while (join[k++])
			buffer[i + k - 1] = join[k - 1];
	if (k >= 1)
		k--;
	buffer[i + k] = '\0';
	free(temp);
	free(join);
}

char	*return_buffer(char **buffer)
{
	char	*str;
	int		i;

	if (!(*buffer) || (*buffer) == NULL || (*buffer)[0] == '\0')
		return (NULL);
	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i])
		i++;
	if ((*buffer)[i++])
		i++;
	str = malloc(sizeof(char) * i);
	str[i - 1] = '\0';
	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i])
	{
		str[i] = (*buffer)[i];
		i++;
	}
	if ((*buffer)[i] == '\n')
		str[i] = (*buffer)[i];
	if ((*buffer)[i] == '\n')
		str[++i] = '\0';
	next_buffer(buffer, i);
	return (str);
}

void	next_buffer(char **buffer, int i)
{
	char	*temp;
	int		k;

	k = 0;
	while ((*buffer)[k])
		k++;
	temp = malloc(sizeof(char) * (k - i + 1));
	temp[k - i] = '\0';
	k = -1;
	while ((*buffer)[i + ++k])
		temp[k] = (*buffer)[i + k];
	free((*buffer));
	(*buffer) = malloc(sizeof(char) * (k + 1));
	(*buffer)[k] = '\0';
	k = -1;
	while (temp[++k])
		(*buffer)[k] = temp[k];
	if (k == 0)
	{
		free(*buffer);
		(*buffer) = NULL;
	}
	free(temp);
}

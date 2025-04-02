/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:51:53 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/02 16:32:51 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(char *file)
{
	int		len;
	int		fd;

	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (ft_printe("Error\nWrong file extension\n"), 1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_printe("Error\nFile does not exist\n"), 1);
	close(fd);
	return (0);
}

int	process_line(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->no = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->so = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->ea = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->we = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		data->f = ft_strdup(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		data->c = ft_strdup(line + 2);
	else if (ft_strncmp(line, "\n", 1) == 0)
		return (0);
	else
		return (1);
	return (0);
}

void	ft_put_map(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
	{
		ft_putstr_fd(mat[i], 1);
		i++;
	}
}

int	parse_file(char *file, t_data *data)
{
	int		fd;
	char	*line;

	if (check_file(file) == 1)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_printe("Error\nError opening the file\n"), 1);
	line = get_next_line(fd);
	if (!line)
		return (ft_printe("Error\nError reading the file\n"), close(fd), 1);
	while (line)
	{
		if (process_line(line, data) == 1)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		data->map = ft_append_line(data->map, line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_put_map(data->map);
	return (0);
}

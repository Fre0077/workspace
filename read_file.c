/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:51:53 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/03 10:12:49 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(char *file)
{
	int		len;
	int		fd;

	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (ft_printe("Error\nWrong file extension\n"), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_printe("Error\nFile does not exist\n"), -1);
	return (fd);
}

int	allocate_texture_path(char *path, t_img *img)
{
	img->path = ft_strtrim(path, " \n");
	if (!img->path)
		return (ft_printe("Error\nFunction strtrim failed\n"), 1);
	return (0);
}

int	allocate_color(char *color, t_color *col)
{
	col->color = ft_strtrim(color, " \n");
	if (!col->color)
		return (ft_printe("Error\nFunction strtrim failed\n"), 1);
	return (0);
}

int	process_line(char *line, t_data *data)
{
	int	ret;

	if (ft_strncmp(line, "NO ", 3) == 0)
		ret = allocate_texture_path(line + 3, data->no);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		ret = allocate_texture_path(line + 3, data->so);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		ret = allocate_texture_path(line + 3, data->ea);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		ret = allocate_texture_path(line + 3, data->we);
	else if (ft_strncmp(line, "F ", 2) == 0)
		ret = allocate_color(line + 2, data->f);
	else if (ft_strncmp(line, "C ", 2) == 0)
		ret = allocate_color(line + 2, data->c);
	else if (ft_strncmp(line, "\n", 1) == 0)
		return (0);
	else
		return (2);
	return (ret);
}

void	read_map(char *line, t_data *data, int fd)
{
	while (line)
	{
		data->map = ft_append_line(data->map, line);
		line = get_next_line(fd);
	}
}

int	read_file(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		ret;

	fd = check_file(file);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	if (!line)
		return (ft_printe("Error\nError reading the file\n"), close(fd), 1);
	while (line)
	{
		ret = process_line(line, data);
		if (ret == 1)
			return (ft_printe("Error\nError processing the line\n"),
				free(line), close(fd), data->status = 1, ft_close(data), 1);
		else if (ret == 2)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	read_map(line, data, fd);
	close(fd);
	return (0);
}

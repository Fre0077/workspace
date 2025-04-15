/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:51:53 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/15 11:07:33 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_texture_path(char *path, t_ft_img *img)
{
	if (img->path)
		free(img->path);
	img->path = ft_strtrim(path, " \n");
	if (!img->path)
		return (ft_printe("Error\nFunction strtrim failed\n"), 1);
	return (0);
}

int	allocate_color(char *color, t_color *col)
{
	if (col->color)
		free(col->color);
	col->color = ft_strtrim(color, " \n");
	if (!col->color)
		return (ft_printe("Error\nFunction strtrim failed\n"), 1);
	return (0);
}

int	process_line(char *line, t_data *data)
{
	int	ret;

	if (ft_strncmp(line, "NO ", 3) == 0)
		ret = allocate_texture_path(line + 3, data->textures[NORTH]);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		ret = allocate_texture_path(line + 3, data->textures[SOUTH]);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		ret = allocate_texture_path(line + 3, data->textures[EAST]);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		ret = allocate_texture_path(line + 3, data->textures[WEST]);
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

int	read_map(char *line, t_data *data, int fd)
{
	int	i;
	int	j;

	while (line)
	{
		line = ft_strtrim_free(line, "\n");
		data->map = ft_append_line(data->map, line);
		data->zone_map = ft_append_line(data->zone_map, ft_strdup(line));
		line = get_next_line(fd);
	}
	i = -1;
	while (data->zone_map && data->zone_map[++i])
	{
		j = -1;
		while (data->zone_map[i][++j])
			if (ft_strchr("NSWE", data->map[i][j]))
				data->zone_map[i][j] = '0';
	}
	if (map_checks(data))
		return (1);
	return (0);
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
		return (ft_printe("Error\nInvalid file\n"), data->status = 1,
			close(fd), 1);
	while (line)
	{
		ret = process_line(line, data);
		if (ret == 1)
			return (free(line), close(fd), data->status = 1, ft_close(data), 1);
		else if (ret == 2)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (read_map(line, data, fd))
		return (close(fd), data->status = 1, ft_close(data), 1);
	close(fd);
	return (0);
}

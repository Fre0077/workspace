/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:20:33 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/15 11:24:04 by alborghi         ###   ########.fr       */
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

int	check_player(t_data *data)
{
	int	i;
	int	player_check;

	i = 0;
	player_check = 0;
	while (data->map && data->map[i])
	{
		if (ft_strchr(data->map[i], 'N') || ft_strchr(data->map[i], 'S')
			|| ft_strchr(data->map[i], 'E') || ft_strchr(data->map[i], 'W'))
			player_check++;
		i++;
	}
	if (player_check > 1)
		return (ft_printe("Error\nMultiple player found\n"), 1);
	else if (player_check == 0)
		return (ft_printe("Error\nNo player found\n"), 1);
	return (0);
}

int	check_char(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map && data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
			if (!ft_strchr("01NSWEP \n", data->map[i][j]))
				return (ft_printe("Error\nInvalid character in map\n"), 1);
	}
	return (0);
}

int	check_auschwitz(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map && data->map[++i])
	{
		j = -1;
		while (data->map && data->map[i][++j])
		{
			if ((i - 1 < 0 || data->map[i + 1] == NULL
					|| j - 1 < 0 || data->map[i][j + 1] == '\0')
				&& ft_strchr("0NSWE", data->map[i][j]))
				return (ft_printe("Error\nInvalid map\n"), 1);
			if (ft_strchr("0NSWE", data->map[i][j]))
			{
				if (strchr(" \0", data->map[i][j - 1]) != NULL
					|| strchr(" \0", data->map[i][j + 1]) != NULL
					|| strchr(" \0", data->map[i - 1][j]) != NULL
					|| strchr(" \0", data->map[i + 1][j]) != NULL)
					return (ft_printe("Error\nGod divine light\n"), 1);
			}
		}
	}
	return (0);
}

int	map_checks(t_data *data)
{
	if (!data->map)
		return (ft_printe("Error\nMap not found\n"), 1);
	if (check_player(data))
		return (1);
	if (check_char(data))
		return (1);
	if (check_auschwitz(data))
		return (1);
	return (0);
}

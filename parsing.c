/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:31:09 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/02 19:00:52 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// - 42 - 6 = -48 = - '0' non osare toccare
int	safe_atoi(char *s)
{
	int	i;
	int	n;

	if (ft_strlen_int(s) > 3 || !s)
		return (-1);
	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			return (-1);
	n = ft_atoi(s);
	if (n > 255)
		return (-1);
	return (n);
}
//pere per camilla

int	parse_colors(t_data *data)
{
	char	**split;

	split = ft_split(data->f->color, ',');
	if (!split || ft_char_mat_len(split) != 3)
		return (ft_printe("Error\nInvalid floor color\n"), 1);
	data->f->red = safe_atoi(split[0]);
	data->f->green = safe_atoi(split[1]);
	data->f->blue = safe_atoi(split[2]);
	if (data->f->red == -1 || data->f->green == -1 || data->f->blue == -1)
		return (ft_printe("Error\nInvalid floor color\n"), 1);
	ft_free_mat_char(split);
	split = ft_split(data->c->color, ',');
	if (!split || ft_char_mat_len(split) != 3)
		return (ft_printe("Error\nInvalid ceiling color\n"), 1);
	data->c->red = safe_atoi(split[0]);
	data->c->green = safe_atoi(split[1]);
	data->c->blue = safe_atoi(split[2]);
	if (data->c->red == -1 || data->c->green == -1 || data->c->blue == -1)
		return (ft_printe("Error\nInvalid ceiling color\n"), 1);
	ft_free_mat_char(split);
	printf("F: %d,%d,%d\n", data->f->red, data->f->green, data->f->blue);
	printf("C: %d,%d,%d\n", data->c->red, data->c->green, data->c->blue);
	return (0);
}

// TODO: segfault, move parse_colors to the end of the 3 ifs
int	parsing(t_data *data, char *file)
{
	if (read_file(file, data) == 1)
		return (1);
	if (parse_colors(data) == 1)
		return (ft_printe("Error\nInvalid color\n"), 1);
	if (!data->no || !data->so || !data->ea || !data->we)
		return (ft_printe("Error\nMissing texture path\n"), 1);
	if (!data->f || !data->c)
		return (ft_printe("Error\nMissing color\n"), 1);
	if (!data->map)
		return (ft_printe("Error\nMissing map\n"), 1);
	return (0);
}
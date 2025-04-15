/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:31:09 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/15 10:16:18 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_colors(t_data *data)
{
	char	**split;

	split = ft_split(data->f->color, ',');
	if (!split || ft_char_mat_len(split) != 3)
		return (ft_printe("Error\nInvalid floor color\n"),
			ft_free_mat_char(split), 1);
	data->f->red = safe_atoi(split[0]);
	data->f->green = safe_atoi(split[1]);
	data->f->blue = safe_atoi(split[2]);
	if (data->f->red == -1 || data->f->green == -1 || data->f->blue == -1)
		return (ft_printe("Error\nInvalid floor color\n"),
			ft_free_mat_char(split), 1);
	ft_free_mat_char(split);
	split = ft_split(data->c->color, ',');
	if (!split || ft_char_mat_len(split) != 3)
		return (ft_printe("Error\nInvalid ceiling color\n"),
			ft_free_mat_char(split), 1);
	data->c->red = safe_atoi(split[0]);
	data->c->green = safe_atoi(split[1]);
	data->c->blue = safe_atoi(split[2]);
	if (data->c->red == -1 || data->c->green == -1 || data->c->blue == -1)
		return (ft_printe("Error\nInvalid ceiling color\n"),
			ft_free_mat_char(split), 1);
	ft_free_mat_char(split);
	return (0);
}

int	mlx_fa_schifo(t_ft_img *img, t_data *data)
{
	img->img = mlx_xpm_file_to_image(data->mlx,
			img->path,
			&img->width, &img->height);
	if (!img->img)
		return (1);
	img->img->data = mlx_get_data_addr(
			img->img,
			&img->bpp,
			&img->line_len,
			&img->endian);
	if (!img->img->data)
		return (1);
	img->data
		= (unsigned int *)img->img->data;
	return (0);
}

int	load_textures(t_data *data)
{
	if (mlx_fa_schifo(data->textures[EAST], data))
		return (ft_printe("Error\nInvalid east texture\n"), 1);
	if (mlx_fa_schifo(data->textures[SOUTH], data))
		return (ft_printe("Error\nInvalid south texture\n"), 1);
	if (mlx_fa_schifo(data->textures[WEST], data))
		return (ft_printe("Error\nInvalid west texture\n"), 1);
	if (mlx_fa_schifo(data->textures[NORTH], data))
		return (ft_printe("Error\nInvalid north texture\n"), 1);
	if (mlx_fa_schifo(data->textures[8], data))
		return (ft_printe("Error\nInvalid map texture\n"), 1);
	if (mlx_fa_schifo(data->textures[4], data))
		return (ft_printe("Error\nInvalid minimap texture\n"), 1);
	if (mlx_fa_schifo(data->textures[5], data))
		return (ft_printe("Error\nInvalid minimap texture\n"), 1);
	if (mlx_fa_schifo(data->textures[6], data))
		return (ft_printe("Error\nInvalid minimap texture\n"), 1);
	if (mlx_fa_schifo(data->textures[7], data))
		return (ft_printe("Error\nInvalid minimap texture\n"), 1);
	if (mlx_fa_schifo(data->hand, data))
		return (ft_printe("Error\nInvalid hand texture\n"), 1);
	return (0);
}

void	find_player(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (ft_strchr("NSWE", data->map[i][j]))
			{
				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
				if (data->map[i][j] == 'N')
					data->player.angle = 270;
				else if (data->map[i][j] == 'S')
					data->player.angle = 90;
				else if (data->map[i][j] == 'E')
					data->player.angle = 0;
				else if (data->map[i][j] == 'W')
					data->player.angle = 180;
				return ;
			}
		}
	}
}

int	parsing(t_data *data)
{
	if (!data->f->color || !data->c->color)
		return (ft_printe("Error\nMissing color\n"), 1);
	if (!data->textures[EAST]->path || !data->textures[SOUTH]->path
		|| !data->textures[WEST]->path || !data->textures[NORTH]->path)
		return (ft_printe("Error\nMissing texture path\n"), 1);
	if (!data->map)
		return (ft_printe("Error\nMissing map\n"), 1);
	if (load_colors(data))
		return (1);
	if (load_textures(data))
		return (1);
	find_player(data);
	data->pos.x = floor(data->player.x);
	data->pos.y = floor(data->player.y);
	return (0);
}

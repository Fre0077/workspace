/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:35:50 by fde-sant          #+#    #+#             */
/*   Updated: 2025/04/15 10:54:28 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_pos(t_data *data)
{
	if (data->pos.x != floor(data->player.x)
		|| data->pos.y != floor(data->player.y))
	{
		data->map[(int)data->player.y][(int)data->player.x] = data->map
		[(int)data->pos.y][(int)data->pos.x];
		data->map[(int)data->pos.y][(int)data->pos.x] = data->zone_map
		[(int)data->pos.y][(int)data->pos.x];
		data->pos.x = floor(data->player.x);
		data->pos.y = floor(data->player.y);
	}
}

void	draw_head(t_data *data, int x, int y)
{
	int				i;
	int				j;
	unsigned int	color;

	y = y * 10 + 20;
	x = x * 10 + 20;
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			color = data->textures[4]->data
			[(i * 36 * data->textures[4]->line_len / 4) + j * 36];
			data->screen->data
			[((y + i) * data->screen->line_length / 4) + (x + j)] = color;
		}
	}
}

void	draw_div12(t_data *data, int x, int y, int f)
{
	int				i;
	int				j;
	unsigned int	color;

	y = y * 10 + 20;
	x = x * 10 + 20;
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			color = data->textures[f]->data
			[(i * 12 * data->textures[f]->line_len / 4) + j * 12];
			data->screen->data
			[((y + i) * data->screen->line_length / 4) + (x + j)] = color;
		}
	}
}

void	draw_map(t_data *data)
{
	int			i;
	int			j;
	t_viktor	offset;

	offset.x = (data->player.x - 7) * ((floor(data->player.x) - 7) > 0);
	offset.y = (data->player.y - 7) * ((floor(data->player.y) - 7) > 0);
	i = -1;
	while (++i < 14 && data->map[i + (int)offset.y])
	{
		j = -1;
		while (++j < 14 && j + (int)offset.x < ft_strlen_int(data->map
				[i + (int)offset.y]))
		{
			if (data->map[i + (int)offset.y][j + (int)offset.x] == '1')
				draw_div12(data, j, i, 5);
			else if (data->map[i + (int)offset.y][j + (int)offset.x] == '0')
				draw_div12(data, j, i, 6);
			else if (ft_strchr("pP", data->map[i + (int)offset.y]
					[j + (int)offset.x]))
				draw_div12(data, j, i, 7);
			else if (ft_strchr("NSEW", data->map[i + (int)offset.y]
					[j + (int)offset.x]))
				draw_head(data, j, i);
		}
	}
}

void	minimapping(t_data *data)
{
	int				i;
	int				j;
	unsigned int	color;

	i = -1;
	while (++i < data->textures[8]->height)
	{
		j = -1;
		while (++j < data->textures[8]->width)
		{
			color = data->textures[8]->data
			[(i * data->textures[8]->line_len / 4) + j];
			if (color != 0xFF000000)
				data->screen->data
				[((i + 10) * data->screen->line_length / 4) + j + 10] = color;
		}
	}
	draw_map(data);
}

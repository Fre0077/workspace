/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:38:20 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/11 19:23:32 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	side(t_ray ray)
{
	if (ray.nose.angle == 0)
	{
		if (ray.nose.y > 0)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (ray.nose.x > 0)
			return (WEST);
		else
			return (EAST);
	}
}

int	get_wall_color(t_data *data, t_ray ray, int y, double ang[2])
{
	int			color;
	int			txt_x;
	int			pixel_index;
	int			tex_side;
	double		wall_x;

	if (ray.nose.angle)
		wall_x = data->player.y + ray.dist * ang[0];
	else
		wall_x = data->player.x + ray.dist * ang[1];
	wall_x -= (int)wall_x;
	tex_side = side(ray);
	txt_x = (wall_x * (TILE_SIZE - 1));
	if ((ray.nose.angle == 1 && ray.nose.x < 0) || (ray.nose.angle == 0
		&& ray.nose.y > 0))
		txt_x = TILE_SIZE - txt_x - 1;
	pixel_index = (y * data->textures[tex_side]->line_len / 4) + txt_x;
	color = data->textures[tex_side]->data[pixel_index];
	return (color);
}
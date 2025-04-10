/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:38:20 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/10 14:44:41 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calc_wall_x(t_data *data, t_ray ray)
{
	double		wall_x;

	if (ray.nose.angle)
		wall_x = data->player.y + ray.dist * sin(ray.angle);
	else
		wall_x = data->player.x + ray.dist * cos(ray.angle);
	wall_x -= (int)wall_x;
	return (wall_x);
}

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

int	get_wall_color(t_data *data, int wall, t_ray *ray, int y)
{
	int			color;
	int			txt_x;
	int			pixel_index;

	(void)wall;
	txt_x = (int)(calc_wall_x(data, *ray) * (TILE_SIZE - 1));
	if ((ray->nose.angle == 1 && ray->nose.x < 0) || (ray->nose.angle == 0
		&& ray->nose.y > 0))
		txt_x = TILE_SIZE - txt_x - 1;
	ray->wall_i = (int)((int)ray->pos & (TILE_SIZE - 1));
	ray->pos += ray->step;
	pixel_index = (y * data->textures[side(*ray)]->line_len / 4) + txt_x;
	color = data->textures[side(*ray)]->data[pixel_index];
	return (color);
}
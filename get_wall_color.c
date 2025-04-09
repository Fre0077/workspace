/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:38:20 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/09 18:58:15 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calc_wall_x(t_data *data, t_ray ray)
{
	double		wall_x;

	if (ray.nose.angle)
		wall_x = data->player.y + ray.dist * sin(data->player.angle);
		// wall_x = data->player.y + ray.dist * sin(ray.angle);
	else
		wall_x = data->player.x + ray.dist * cos(data->player.angle);
		// wall_x = data->player.x + ray.dist * cos(ray.angle);
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

int	get_wall_color(t_data *data, int wall, t_ray ray)
{
	int			color;
	double		wall_x;
	int			txt_x;
	char		c;

	(void)wall;
	wall_x = calc_wall_x(data, ray);
	txt_x = (int)(wall_x * TILE_SIZE);
	// printf("wall_x: %f\n", wall_x);
	// printf("txt_x: %d\n", txt_x);
	if ((ray.nose.angle == 1 && ray.nose.x < 0) || (ray.nose.angle == 0
		&& ray.nose.y > 0))
		txt_x = TILE_SIZE - txt_x - 1;
	ray.wall_i = (int)((int)ray.pos & (TILE_SIZE - 1));
	// printf("ray.wall_i: %f\n", ray.wall_i);
	ray.pos += ray.step;
	// printf("ray.pos: %f\n", ray.pos);
	// color = data->textures[side(ray)]->img->data[(int)(ray.wall_i * (data->textures[side(ray)]->line_len / 4) + txt_x)];
	c = data->textures[side(ray)]->img->data[(int)(TILE_SIZE * ray.wall_i + txt_x)];
	color = c << 16 | c << 8 | c;
	// printf("color: %d\n", color);
	// printf("data: %c\n", data->textures[side(ray)]->img->data[(int)(TILE_SIZE * ray.wall_i + txt_x)]);
	// printf("data: %d\n", data->textures[side(ray)]->img->data[(int)(TILE_SIZE * ray.wall_i + txt_x)]);
	return (color);
}
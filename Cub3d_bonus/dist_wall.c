/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:21:12 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/14 17:22:32 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	zero_case(t_data *data, t_viktor dir, double angle, t_ray *ray)
{
	double		d[3];
	t_viktor	tm;

	tm = data->player;
	d[0] = 0;
	d[1] = 0;
	d[2] = 0;
	while (!hit(data, tm))
	{
		if (((int)angle / 90) % 2 == 0)
		{
			d[0] = fabs(((int)tm.x + (dir.x > 0)) - data->player.x);
			tm.x += dir.x;
			d[2] = d[0];
		}
		else
		{
			d[1] = fabs(((int)tm.y + (dir.y > 0)) - data->player.y);
			tm.y += dir.y;
			d[2] = d[1];
		}
	}
	ray->seen_block = data->map[(int)tm.y][(int)tm.x];
	return (ray->nose = (t_viktor){dir.x, dir.y, (d[2] == d[0])}, d[2]);
}

void	first_step(double d[], t_viktor *tmp, t_viktor player, t_viktor dir)
{
	d[0] = fabs(((int)player.x + (dir.x > 0)) - player.x) / cos(rad(-1));
	d[1] = fabs(((int)player.y + (dir.y > 0)) - player.y) / sin(rad(-1));
	if (d[0] <= d[1])
	{
		tmp->x += dir.x;
		d[2] = d[0];
	}
	else
	{
		tmp->y += dir.y;
		d[2] = d[1];
	}
}

double	calc_dist(t_data *data, double angle, t_ray *ray, t_viktor *t)
{
	t_viktor	dir;
	double		d[3];

	rad(ray->angle);
	dir.x = cos(angle * RAD) / fabs(cos(angle * RAD));
	dir.y = sin(angle * RAD) / fabs(sin(angle * RAD));
	if (isnan(dir.y))
		dir.y = 1;
	if (r(angle) == 0)
		return (zero_case(data, dir, angle, ray));
	first_step(d, t, data->player, dir);
	while (!hit(data, *t))
	{
		d[0] = fabs(((int)t->x + (dir.x > 0)) - data->player.x) / cos(rad(-1));
		d[1] = fabs(((int)t->y + (dir.y > 0)) - data->player.y) / sin(rad(-1));
		t->x += (dir.x * (d[0] <= d[1]));
		t->y += (dir.y * (d[0] >= d[1]));
		d[2] = d[1];
		if (d[0] < d[1])
			d[2] = d[0];
	}
	ray->seen_block = data->map[(int)t->y][(int)t->x];
	return (ray->nose = (t_viktor){dir.x, dir.y, (d[2] == d[0])}, d[2]);
}

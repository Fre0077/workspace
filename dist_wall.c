/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:21:12 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/09 16:18:45 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	zero_case(t_data *data, t_viktor *tm, t_viktor dir, int witch)
{
	double		dist[3];

	dist[0] = 0;
	dist[1] = 0;
	dist[2] = 0;
	while (!hit(data, *tm))
	{
		if (witch % 2 == 0)
		{
			dist[0] = fabs(((int)tm->x + (dir.x > 0)) - data->player.x);
			tm->x += dir.x;
			dist[2] = dist[0];
		}
		else
		{
			dist[1] = fabs(((int)tm->y + (dir.y > 0)) - data->player.y);
			tm->y += dir.y;
			dist[2] = dist[1];
		}
	}
	return (dist[2]);
}

void	first_step(double dist[], t_viktor *tmp, t_viktor player, t_viktor dir)
{
	dist[0] = fabs(((int)player.x + (dir.x > 0)) - player.x) / cos(rad(-1));
	dist[1] = fabs(((int)player.y + (dir.y > 0)) - player.y) / sin(rad(-1));
	if (dist[0] <= dist[1])
	{
		tmp->x += dir.x;
		dist[2] = dist[0];
	}
	else
	{
		tmp->y += dir.y;
		dist[2] = dist[1];
	}
}

double	calculate_dist(t_data *data, double angle, double ra, t_viktor *nose)
{
	t_viktor	tm;
	t_viktor	dir;
	double		d[3];

	tm = data->player;
	rad(ra);
	dir.x = cos(angle * (M_PI / 180.0)) / fabs(cos(angle * (M_PI / 180.0)));
	dir.y = sin(angle * (M_PI / 180.0)) / fabs(sin(angle * (M_PI / 180.0)));
	if (isnan(dir.y))
		dir.y = 1;
	if (r(angle) == 0)
		return (zero_case(data, &tm, dir, ((int)angle) / 90));
	first_step(d, &tm, data->player, dir);
	while (!hit(data, tm))
	{
		d[0] = fabs(((int)tm.x + (dir.x > 0)) - data->player.x) / cos(rad(-1));
		d[1] = fabs(((int)tm.y + (dir.y > 0)) - data->player.y) / sin(rad(-1));
		tm.x += (dir.x * (d[0] < d[1]));
		tm.y += (dir.y * (d[0] > d[1]));
		d[2] = d[1];
		if (d[0] < d[1])
			d[2] = d[0];
		*nose = (t_viktor){dir.x, dir.y, (d[2] == d[0])}; //TODO: watch the 45 out
	}
	return (d[2]);
}

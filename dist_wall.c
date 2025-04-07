/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:21:12 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/07 18:52:07 by fde-sant         ###   ########.fr       */
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
	return(dist[2]);
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

double calculate_dist(t_data *data, double angle, double ra)
{
	t_viktor	tm;
	t_viktor	dir;
	double		dis[3];

	tm = data->player;
	rad(ra);
	dir.x = cos(angle * (M_PI / 180.0)) / fabs(cos(angle * (M_PI / 180.0)));
	dir.y = sin(angle * (M_PI / 180.0)) / fabs(sin(angle * (M_PI / 180.0)));
	if (isnan(dir.y))
		dir.y = 1;
	if (r(angle) == 0)
		return (zero_case(data, &tm, dir, ((int)angle) / 90));
	first_step(dis, &tm, data->player, dir);
	while (!hit(data, tm))
	{
		dis[0] = fabs(((int)tm.x + (dir.x > 0)) - data->player.x) / cos(rad(-1));
		dis[1] = fabs(((int)tm.y + (dir.y > 0)) - data->player.y) / sin(rad(-1));
		tm.x += (dir.x * (dis[0] < dis[1]));
		tm.y += (dir.y * (dis[0] > dis[1]));
		dis[2] = dis[1];
		if (dis[0] < dis[1])
			dis[2] = dis[0];
	}
	return(dis[2]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_wallp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:22:03 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/14 17:24:11 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_viktor	calc_distp(t_data *data, double angle, double ra)
{
	t_viktor	tm;
	t_viktor	dir;
	double		d[3];

	tm = data->player;
	rad(ra);
	dir.x = cos(angle * RAD) / fabs(cos(angle * RAD));
	dir.y = sin(angle * RAD) / fabs(sin(angle * RAD));
	if (isnan(dir.y))
		dir.y = 1;
	if (r(angle) == 0)
		return (zero_casep(data, &tm, dir, ((int)angle) / 90));
	first_stepp(d, &tm, data->player, dir);
	while (!hitp(data, tm))
	{
		d[0] = fabs(((int)tm.x + (dir.x > 0)) - data->player.x) / cos(rad(-1));
		d[1] = fabs(((int)tm.y + (dir.y > 0)) - data->player.y) / sin(rad(-1));
		tm.x += (dir.x * (d[0] <= d[1]));
		tm.y += (dir.y * (d[0] >= d[1]));
	}
	return (tm);
}

t_viktor	zero_casep(t_data *data, t_viktor *tm, t_viktor dir, int witch)
{
	double		dist[3];

	dist[0] = 0;
	dist[1] = 0;
	dist[2] = 0;
	while (!hitp(data, *tm))
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
	return (*tm);
}

void	first_stepp(double dist[], t_viktor *tmp, t_viktor player, t_viktor dir)
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

int	hitp(t_data *data, t_viktor tmp)
{
	char	c;

	if (tmp.x < 0 || tmp.y < 0)
		return (0);
	c = data->map[(int)tmp.y][(int)tmp.x];
	if (c == '1' || c == 'P' || c == 'p')
		return (1);
	else
		return (0);
}

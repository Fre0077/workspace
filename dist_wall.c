/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:21:12 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/07 13:52:49 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit(t_data *data, t_viktor tmp)
{
	char	c;

	if (tmp.x < 0 || tmp.y < 0)
		return (0);
	c = data->map[(int)tmp.y][(int)tmp.x];
	if (c == '1')
		return (1);
	else
		return (0);
}

double	r(double angle)
{
	int	tmp;

	tmp = angle;
	angle -= tmp;
	tmp = tmp % 90;
	return (angle + tmp);
}

double	rad(double rad)
{
	static double radd;

	if (rad != -1)
		radd = rad;
	return (radd);
}

double	mult_of_90(double num, char direct)
{
	double rest;

	rest = r(num);
	if (rest == 0 && direct == '<')
		num = (int)(((int)(num / 90) - 1) * 90);
	else if (direct == '<')
		num = (int)(((int)(num / 90)) * 90);
	else
		num = (int)(((int)(num / 90) + 1) * 90);
	return (num);
}

double	calculate_angle(double angle, double cost, char sign)
{
	double	supp;

	if (sign == '-')
	{
		angle = angle - cost;
		supp = mult_of_90(angle, '<');
		if ((int)(supp / 90) % 2 == 1)
			supp = mult_of_90(angle, '>');
		return (fabs(supp - angle));
	}
	else
	{
		angle = angle + cost;
		supp = mult_of_90(angle, '>');
		if ((int)(supp / 90) % 2 == 1)
			supp = mult_of_90(angle, '<');
		return (fabs(supp - angle));
	}
}

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

void	put_texture(t_data *data, int i, double dist, double corr_angle)
{
	int		j;
	int		color;
	int		wall;

	//(void)corr_angle;
	if (dist <= 1)
		wall = HEIGHT;
	else
		wall = (HEIGHT / (dist * cos(corr_angle * (M_PI / 180.0))));
	j = -1;
	while (++j < HEIGHT)
	{
		if (j < (HEIGHT - wall) / 2)
			color = data->c->red << 16 | data->c->green << 8 | data->c->blue;
		else if (j < (HEIGHT - ((HEIGHT - wall) / 2)))
			color = 0x00FF00;
		else
			color = data->f->red << 16 | data->f->green << 8 | data->f->blue;
		*(unsigned int *)(data->screen->addr + (j * data->screen->line_length)
				+ (i * (data->screen->bpp / 8))) = color;
	}
}

void calculate_img(t_data *data)
{
	int		i;
	double	cost;
	double	dist;

	i = -1;
	cost = (double)FOV / (double)WIDTH;
	while (++i < WIDTH / 2)
	{
		dist = calculate_dist(data, (data->player.angle - (cost * i)),
								calculate_angle(data->player.angle,
									(cost * i), '-') * (M_PI / 180.0));
		put_texture(data, 719 - i, dist, ( - (cost * i)));
		dist = calculate_dist(data, (data->player.angle + (cost * i)),
								calculate_angle(data->player.angle,
									(cost * i), '+') * (M_PI / 180.0));
		put_texture(data, i + 720, dist, (cost * i));
	}
}

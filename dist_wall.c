/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:21:12 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/06 17:03:39 by fre007           ###   ########.fr       */
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
	//printf("#########%f\n", radd);
	return (radd);
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
			//printf("------\ncalc: %d  -  %f\n", ((int)tm->x + (dir.x > 0)), data->player.x);
			//printf("dist0: %f\n-------\n", dist[0]);
			tm->x += dir.x;
			dist[2] = dist[0];
		}
		else
		{
			dist[1] = fabs(((int)tm->y + (dir.y > 0)) - data->player.y);
			tm->y += dir.y;
			dist[2] = dist[1];
		}
		//printf("tmp pos: %f %f    witch: %d\n", tm->x, tm->y, witch);
	}
	return(dist[2]);
}

void	first_step(double dist[], t_viktor *tmp, t_viktor player, t_viktor dir)
{
	dist[0] = fabs(((int)player.x + (dir.x > 0)) - player.x) / cos(rad(-1));
	dist[1] = fabs(((int)player.y + (dir.y > 0)) - player.y) / sin(rad(-1));
	//printf("calc: %f  -  %f\n", ((int)player.x + dir.x), player.x);
	//printf("calc: %f  -  %f\n", ((int)player.y + dir.y), player.y);
	//printf("angle: %f\n", r(angle));
	//printf("cos: %f\n", cos(r(angle)));
	//printf("sin: %f\n", sin(r(angle)));
	//printf("first-dist0: %f\n", dist[0]);
	//printf("first-dist1: %f\n", dist[1]);
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
	//printf("first tmp pos: %f %f\n", tmp->x, tmp->y);
}

double calculate_dist(t_data *data, double angle, double ra)
{
	t_viktor	tm;
	t_viktor	dir;
	double		dist[3]; //dist[0]:x dist[1]:y

	tm = data->player;
	rad(ra);
	dir.x = cos(angle * (M_PI / 180.0)) / fabs(cos(angle * (M_PI / 180.0)));
	dir.y = sin(angle * (M_PI / 180.0)) / fabs(sin(angle * (M_PI / 180.0)));
	if (isnan(dir.y))
		dir.y = 1;
	//printf("dir.x: %f\n", dir.x);
	//printf("dir.y: %f\n", dir.y);
	if (r(angle) == 0)
		return (zero_case(data, &tm, dir, ((int)angle) / 90));
	first_step(dist, &tm, data->player, dir);
	//printf("dist0: %f\n", dist[0]);
	//printf("dist1: %f\n", dist[1]);
	while (!hit(data, tm))
	{
		dist[0] = fabs(((int)tm.x + (dir.x > 0)) - data->player.x) / cos(rad(-1));
		dist[1] = fabs(((int)tm.y + (dir.y > 0)) - data->player.y) / sin(rad(-1));
		if (dist[0] < dist[1])
		{
			//printf("------\n");
			//printf("calc: %f  -  %f\n", ((int)tm.x + dir.x), data->player.x);
			//printf("angle: %f\n", r(angle));
			//printf("cos: %f\n", cos(r(angle)));
			//printf("dist0: %f\n", dist[0]);
			tm.x += dir.x;
			dist[2] = dist[0];
			//printf("dist2: %f\n", dist[2]);
			//printf("-------\n");
		}
		else
		{
			//printf("dist1: %f\n", dist[1]);
			tm.y += dir.y;
			dist[2] = dist[1];
		}
		//printf("tmp pos: %f %f\n", tm.x, tm.y);
	}
	return(dist[2]);
}

void	put_texture(t_data *data, int i, double dist)
{
	int		j;
	int		color;
	int		wall;

	//ft_printf("cazzo\n");
	//printf("dist: %f\n", ((double)dist));
	if (dist <= 1)
		wall = HEIGHT;
	else
		wall = (HEIGHT / dist);
	//printf("wall: %d", wall);
	//ft_printf("cazzo  %d   %d\n", wall, dist);
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
		//ft_printf("j: %d", j);
	}
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
	//printf("mult_of_90: %f\n", num);
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
		//printf("calculate_angle: %f  supp: %f   angle: %f\n", fabs(supp - angle), supp, angle);
		return (fabs(supp - angle));
	}
	else
	{
		angle = angle + cost;
		supp = mult_of_90(angle, '>');
		if ((int)(supp / 90) % 2 == 1)
			supp = mult_of_90(angle, '<');
		//printf("calculate_angle: %f  supp: %f   angle: %f\n", fabs(supp - angle), supp, angle);
		return (fabs(supp - angle));
	}
}

void calculate_img(t_data *data)
{
	int		i;
	//int		j = 720;
	double	cost;
	double	dist;

	//printf("player pos: %f %f\n", data->player.x, data->player.y);
	i = -1;
	cost = (double)FOV / (double)WIDTH;
	//printf("###########cost: %f\n", cost);
	//printf("###########angle: %f\n", data->player.angle);
	//data->player.angle = 359;
	while (++i < WIDTH / 2)
	{
		//printf("##############\n");
		//printf("1calc-angle: %f\n", calculate_angle(data->player.angle, (cost * i), '-'));
		dist = calculate_dist(data, (data->player.angle - (cost * i)), calculate_angle(data->player.angle, (cost * i), '-') * (M_PI / 180.0));
		//printf("dist[%d]: %f\n", 719 - i, dist);
		put_texture(data, 719 - i, dist);
		//printf("2calc-angle: %f\n", calculate_angle(data->player.angle, (cost * i), '+'));
		dist = calculate_dist(data, (data->player.angle + (cost * i)), calculate_angle(data->player.angle, (cost * i), '+') * (M_PI / 180.0));
		//printf("dist[%d]: %f\n", i + 720, dist);
		put_texture(data, i + 720, dist);
		//j--;
		//if (j == 0)
		//	break ;
	}
	//exit(0);
}

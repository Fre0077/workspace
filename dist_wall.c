/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:21:12 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/04 17:41:54 by alborghi         ###   ########.fr       */
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

double calculate_dist(t_data *data, double angle)
{
	t_viktor	tmp;
	t_viktor	dir;
	double		dist[2];

	dist[0] = 0;
	tmp = data->player;
	dir = (t_viktor){cos(angle) / fabs(cos(angle)),
			sin(angle) / fabs(sin(angle)), angle};
	// printf("dir: %f %f\n", dir.x, dir.y);
	while (!hit(data, tmp))
	{
		// printf("tmp x: %f dir x: %f player x: %f cos angle: %f\n", tmp.x, dir.x, data->player.x, cos(angle));
		// printf("cateto 1: %f\n", fabs((int)(tmp.x + (dir.x >= 0)) - data->player.x));
		printf("####%f\n", fabs(((int)(tmp.x + (dir.x >= 0)) - data->player.x)));
		dist[0] = fabs(((int)(tmp.x + (dir.x >= 0)) - data->player.x) / cos(angle));
		// printf("tmp y: %f dir y: %f player y: %f cos angle 2: %f\n", tmp.y, dir.y, data->player.y, cos(90 - angle));
		// printf("cateto 2: %f\n", fabs((int)(tmp.y + (dir.y >= 0)) - data->player.y));
		dist[1] = fabs(((int)(tmp.y + (dir.y >= 0)) - data->player.y)
				/ cos(90 - angle));
		if (dist[0] < dist[1])
			tmp.x += dir.x;
		else
			tmp.y += dir.y;
		if (dist[0] > dist[1])
			dist[0] = dist[1];
	}
	// printf("dist: %f\n", dist[0]);
	exit(0);
	return (dist[0]);
}

void	put_texture(t_data *data, int i, int dist)
{
	int		j;
	int		color;
	int		wall;

	if (dist == 0)
		wall = HEIGHT;
	else
		wall = (int)(HEIGHT / dist / 2);
	j = -1;
	while (++j < wall)
	{
		if (j < (HEIGHT - wall) / 2)
			color = data->c->red << 16 | data->c->green << 8 | data->c->blue;
		else if (j < (HEIGHT - wall) / 2 + wall)
			color = 0x00FF00;
		else
			color = data->f->red << 16 | data->f->green << 8 | data->f->blue;
		*(unsigned int *)(data->screen->addr + (j * data->screen->line_length)
				+ (i * (data->screen->bpp / 8))) = color;
	}
}

//	HEIGHT / dist
void calculate_img(t_data *data)
{
	int		i;
	int		dist;

	printf("player pos: %f %f\n", data->player.x, data->player.y);
	i = -1;
	while (++i < WIDTH / 2)
	{
		dist = calculate_dist(data, data->player.angle + (i * (double)FOV / (double)2 / (double)WIDTH));
		// if (dist < 0)
		// 	printf("dist[%d]: %d\n", i, dist);
		put_texture(data, i, dist);
		dist = calculate_dist(data, data->player.angle - (i * (double)FOV / (double)2 / (double)WIDTH));
		// if (dist < 0)
		// 	printf("dist[%d]: %d\n", i, dist);
		put_texture(data, WIDTH - i, dist);
	}
}

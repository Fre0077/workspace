/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:21:12 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/04 18:56:43 by alborghi         ###   ########.fr       */
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

// double calculate_dist(t_data *data, double angle)
// {
// 	t_viktor	tmp;
// 	t_viktor	dir;
// 	double		dist[2];

// 	dist[0] = 0;
// 	tmp = data->player;
// 	dir = (t_viktor){cos(angle) / fabs(cos(angle)),
// 			sin(angle) / fabs(sin(angle)), angle};
	// printf("dir: %f %f\n", dir.x, dir.y);
// 	while (!hit(data, tmp))
// 	{
		// printf("tmp x: %f dir x: %f player x: %f cos angle: %f\n", tmp.x, dir.x, data->player.x, cos(angle));
		// printf("cateto 1: %f\n", fabs((int)(tmp.x + (dir.x >= 0)) - data->player.x));
// 		printf("####%f\n", fabs(((int)(tmp.x + (dir.x >= 0)) - data->player.x)));
// 		dist[0] = fabs(((int)(tmp.x + (dir.x >= 0)) - data->player.x) / cos(angle));
		// printf("tmp y: %f dir y: %f player y: %f cos angle 2: %f\n", tmp.y, dir.y, data->player.y, cos(90 - angle));
		// printf("cateto 2: %f\n", fabs((int)(tmp.y + (dir.y >= 0)) - data->player.y));
// 		dist[1] = fabs(((int)(tmp.y + (dir.y >= 0)) - data->player.y)
// 				/ cos(90 - angle));
// 		if (dist[0] < dist[1])
// 			tmp.x += dir.x;
// 		else
// 			tmp.y += dir.y;
// 		if (dist[0] > dist[1])
// 			dist[0] = dist[1];
// 	}
	// printf("dist: %f\n", dist[0]);
// 	exit(0);
// 	return (dist[0]);
// }

double calculate_dist(t_data *data, double angle)
{
	t_viktor	tmp;
	t_viktor	dir;
	double		dist[2];
	double		coord;

	dist[0] = 0;
	tmp = data->player;
	dir = (t_viktor){cos(angle) / fabs(cos(angle)),
			sin(angle) / fabs(sin(angle)), angle};
	while (!hit(data, tmp))
	{
		coord = data->player.y;
		// coord += ((tmp.x - data->player.x) / cos(angle)) * sin(angle);
		coord += (((int)(tmp.x + (dir.x >= 0)) - data->player.x) / cos(angle)) * sin(angle);
		dist[0] = sqrt(pow(tmp.x - data->player.x, 2) + pow(coord - data->player.y, 2));
		
		coord = data->player.x;
		coord += (((int)(tmp.y + (dir.y >= 0)) - data->player.y) / sin(angle)) * cos(angle);
		dist[1] = sqrt(pow(tmp.y - data->player.y, 2) + pow(coord - data->player.x, 2));
		if (dist[0] < dist[1])
			tmp.x += dir.x;
		else
			tmp.y += dir.y;
		if (dist[0] > dist[1])
			dist[0] = dist[1];
	}
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
		wall = (int)(HEIGHT / dist);
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

// 	HEIGHT / dist
// void calculate_img(t_data *data)
// {
// 	int		i;
// 	int		dist;

// 	dist = calculate_dist(data, data->player.angle + (0 * (double)FOV / (double)2 / (double)WIDTH));
// 	if (dist < 0)
// 		printf("dist[%d]: %d\n", i, dist);
// 	put_texture(data, 0, dist);
// 	i = 0;
// 	while (++i < WIDTH / 2)
// 	{
// 		dist = calculate_dist(data, data->player.angle + (i * (double)FOV / (double)2 / (double)WIDTH));
// 		if (dist < 0)
// 			printf("dist[%d]: %d\n", i, dist);
// 		put_texture(data, i, dist);
// 		dist = calculate_dist(data, data->player.angle - (i * (double)FOV / (double)2 / (double)WIDTH));
// 		if (dist < 0)
// 			printf("dist[%d]: %d\n", i, dist);
// 		put_texture(data, WIDTH - i, dist);
// 	}
// }

void	verLine(t_data *data, int x, int drawStart, int drawEnd, int color)
{
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < drawStart)
			*(unsigned int *)(data->screen->addr + (y * data->screen->line_length)
					+ (x * (data->screen->bpp / 8))) = data->c->red << 16
				| data->c->green << 8 | data->c->blue;
		else if (y >= drawStart && y <= drawEnd)
			*(unsigned int *)(data->screen->addr + (y * data->screen->line_length)
					+ (x * (data->screen->bpp / 8))) = color;
		else
			*(unsigned int *)(data->screen->addr + (y * data->screen->line_length)
					+ (x * (data->screen->bpp / 8))) = data->f->red << 16
				| data->f->green << 8 | data->f->blue;
		y++;
	}
}

void calculate_img(t_data *data)
{
	int		x;
	double	camera_x;
	double	rayDirX;
	double	rayDirY;

	data->ray.dir.x = cos(data->player.angle * M_PI / 180);
	data->ray.dir.y = sin(data->player.angle * M_PI / 180);
	data->ray.plane.x = 0;
	data->ray.plane.y = 0.66;
	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
		rayDirX = data->ray.dir.x + data->ray.plane.x * camera_x;
		rayDirY = data->ray.dir.y + data->ray.plane.y * camera_x;
		int mapX = (int)data->player.x;
		int mapY = (int)data->player.y;
		double sideDistX;
		double sideDistY;
		double deltaDistX;
		double deltaDistY;
		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player.y) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map[mapY][mapX] == '1')
				hit = 1;
		}
		double perpWallDist;
		if (side == 0)
			perpWallDist = sideDistX - deltaDistX;
		else
			perpWallDist = sideDistY - deltaDistY;

		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int color = 0x00FF00;
		verLine(data, x, drawStart, drawEnd, color);
		x++;
	}
}

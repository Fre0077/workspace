/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:47:42 by fde-sant          #+#    #+#             */
/*   Updated: 2025/04/14 17:44:17 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	frame(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->frame++;
	frame_counter(data);
	camera_update(data);
	move_update(data, data->player.angle);
	if (data->screen->img)
		mlx_destroy_image(data->mlx, data->screen->img);
	data->screen->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->screen->img)
		return (ft_printe("Error\nFailed to create image\n"), 1);
	data->screen->addr = mlx_get_data_addr(data->screen->img,
			&data->screen->bpp, &data->screen->line_length,
			&data->screen->endian);
	if (!data->screen->addr)
		return (ft_printe("Error\nFailed to get data address\n"), 1);
	update_player_pos(data);
	data->screen->data = (unsigned int *)data->screen->addr;
	calculate_img(data, (double)FOV / (double)WIDTH);
	mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
	return (0);
}

void	pointer(t_data *data)
{
	int				i;
	int				j;

	i = -17;
	while (++i < 17)
	{
		j = -17;
		while (++j < 17)
			if ((i >= 0 && i < 2) || (j >= 0 && j < 2))
				data->screen->data[((i + HEIGHT / 2)
						* data->screen->line_length / 4)
					+ (j + WIDTH / 2)] = 0x80FFFFFF;
	}
}

void	put_texture(t_data *data, int i, t_ray ray, double corr_angle)
{
	int		j;
	int		color;
	int		wall;
	int		cost;
	double	ang[2];

	wall = (HEIGHT / (ray.dist * cos(corr_angle * RAD)));
	j = -1;
	cost = (HEIGHT - wall) / 2;
	ang[0] = sin(ray.angle);
	ang[1] = cos(ray.angle);
	while (++j < HEIGHT)
	{
		if (j < cost)
			color = data->c->red << 16 | data->c->green << 8 | data->c->blue;
		else if (j < (HEIGHT - cost))
			color = get_wall_color(data, ray,
					(j - cost) * (TILE_SIZE - 1) / wall, ang);
		else
			color = data->f->red << 16 | data->f->green << 8 | data->f->blue;
		data->screen->data[(j * data->screen->line_length / 4) + i] = color;
	}
}

void	handing(t_data *data)
{
	int				i;
	int				j;
	unsigned int	color;
	int				off[2];

	i = -1;
	off[0] = 0;
	off[1] = 0;
	if (data->pkey->w || data->pkey->a || data->pkey->s || data->pkey->d)
	{
		off[0] = 20 * fabs(cos(data->time / 90));
		off[1] = 20 * sin(data->time / (90 - (20 * (data->move_speed == 10))));
	}
	while (++i < data->hand->height)
	{
		j = -1;
		while (++j < data->hand->width)
		{
			color = data->hand->data[(i * data->hand->line_len / 4) + j];
			if (color != 0xFF000000)
				data->screen->data
				[((i + HEIGHT - 256 + off[0]) * data->screen->line_length
						/ 4) + (j + WIDTH / 2 + 300 + off[1])] = color;
		}
	}
}

void	calculate_img(t_data *data, double c)
{
	int			i;
	t_ray		ray;

	i = -1;
	while (++i < WIDTH / 2)
	{
		data->tmp = data->player;
		ray.angle = calc_angle(data->player.angle,
				(c * i), '-') * RAD;
		ray.dist = calc_dist(data, (data->player.angle - (c * i)),
				&ray, &data->tmp);
		ray.angle = (data->player.angle - (c * i)) * RAD;
		data->seen_block = ray.seen_block;
		put_texture(data, (WIDTH / 2) - 1 - i, ray, -(c * i));
		data->tmp = data->player;
		ray.angle = calc_angle(data->player.angle, (c * i), '+') * RAD;
		ray.dist = calc_dist(data, (data->player.angle + (c * i)),
				&ray, &data->tmp);
		ray.angle = (data->player.angle + (c * i)) * RAD;
		data->seen_block = ray.seen_block;
		put_texture(data, i + (WIDTH / 2), ray, (c * i));
	}
	minimapping(data);
	handing(data);
	pointer(data);
}

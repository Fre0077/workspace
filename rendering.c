/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:47:42 by fde-sant          #+#    #+#             */
/*   Updated: 2025/04/11 19:20:42 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (ft_printe("Error\nFailed to create window\n"), 1);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, frame, data);
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_ms);
}

void	frame_counter(t_data *data)
{
	time_t			current_time;

	current_time = get_time();
	free(data->frames);
	data->frames = NULL;
	data->frames = ft_itoa(data->frame);
	mlx_string_put(data->mlx, data->win, WIDTH - 10, 10, 0x00FF00, data->frames);
	if (current_time >= data->frame_time + 1000)
	{
		data->frame = 0;
		data->frame_time = current_time;
	}
}

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
	calculate_img(data, (double)FOV / (double)WIDTH);
	mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
	return (0);
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
			color = get_wall_color(data, ray, (j - cost) * (TILE_SIZE - 1) / wall, ang);
		else
			color = data->f->red << 16 | data->f->green << 8 | data->f->blue;
		data->screen->data[(j * data->screen->line_length / 4) + i] = color;
	}
}

void	calculate_img(t_data *data, double cost)
{
	int			i;
	t_ray		ray;

	i = -1;
	data->screen->data = (unsigned int *)data->screen->addr;
	while (++i < WIDTH / 2)
	{
		ray.angle = calc_angle(data->player.angle,
			(cost * i), '-') * RAD;
		ray.dist = calc_dist(data, (data->player.angle - (cost * i)), &ray);
		ray.angle = (data->player.angle - (cost * i)) * RAD;
		put_texture(data, 719 - i, ray, -(cost * i));
		ray.angle = calc_angle(data->player.angle,
			(cost * i), '+') * RAD;
		ray.dist = calc_dist(data, (data->player.angle + (cost * i)), &ray);
		ray.angle = (data->player.angle + (cost * i)) * RAD;
		put_texture(data, i + 720, ray, (cost * i));
	}
	minimapping(data);
}

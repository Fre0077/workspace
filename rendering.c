/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:47:42 by fde-sant          #+#    #+#             */
/*   Updated: 2025/04/09 18:22:12 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	frame(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	camera_update(data);
	move_update(data, data->player.angle);
	mlx_mouse_hide(data->mlx, data->win);
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
	calculate_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
	return (0);
}

//TODO: []
//TODO: calcolo wall fuori
void	put_texture(t_data *data, int i, t_ray ray, double corr_angle)
{
	int		j;
	int		color;
	int		wall;

	if (ray.dist <= 1)
		wall = HEIGHT;
	else
		wall = (HEIGHT / (ray.dist * cos(corr_angle * (M_PI / 180.0))));
	j = -1;
	ray.step = 1.0 * TILE_SIZE / wall;
	ray.pos = ((HEIGHT - ((HEIGHT - wall) / 2)) - HEIGHT / 2 + wall / 2)
		* ray.step;
	ray.wall_i = 0;
	while (++j < HEIGHT)
	{
		if (j < (HEIGHT - wall) / 2)
			color = data->c->red << 16 | data->c->green << 8 | data->c->blue;
		else if (j < (HEIGHT - ((HEIGHT - wall) / 2)))
			color = get_wall_color(data, wall, ray);
		else
			color = data->f->red << 16 | data->f->green << 8 | data->f->blue;
		*(unsigned int *)(data->screen->addr + (j * data->screen->line_length)
				+ (i * (data->screen->bpp / 8))) = color;
	}
}

void	calculate_img(t_data *data)
{
	int			i;
	double		cost;
	t_ray		ray;

	i = -1;
	cost = (double)FOV / (double)WIDTH;
	while (++i < WIDTH / 2)
	{
		ray.angle = calculate_angle(data->player.angle,
			(cost * i), '-') * (M_PI / 180.0);
		ray.dist = calculate_dist(data, (data->player.angle - (cost * i)),
				ray.angle, &ray.nose);
		put_texture(data, 719 - i, ray, -(cost * i));
		ray.angle = calculate_angle(data->player.angle,
			(cost * i), '+') * (M_PI / 180.0);
			ray.dist = calculate_dist(data, (data->player.angle + (cost * i)),
				ray.angle, &ray.nose);
		put_texture(data, i + 720, ray, (cost * i));
	}
}

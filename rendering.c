/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:47:42 by fde-sant          #+#    #+#             */
/*   Updated: 2025/04/10 18:37:43 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_pos(t_data *data)
{
	if (data->pos.x != floor(data->player.x) || data->pos.y != floor(data->player.y))
	{
		data->map[(int)data->player.y][(int)data->player.x] = data->map[(int)data->pos.y][(int)data->pos.x];
		data->map[(int)data->pos.y][(int)data->pos.x] = '0';
		data->pos.x = floor(data->player.x);
		data->pos.y = floor(data->player.y);
	}
}

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
	update_player_pos(data);
	calculate_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
	return (0);
}

void	put_texture(t_data *data, int i, t_ray ray, double corr_angle)
{
	int		j;
	int		color;
	int		wall;

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
			color = get_wall_color(data, wall, &ray, (j - ((HEIGHT - wall) / 2)) * (TILE_SIZE - 1) / wall);
		else
			color = data->f->red << 16 | data->f->green << 8 | data->f->blue;
		data->screen->data[(j * data->screen->line_length / 4) + i] = color;
	}
}

// void	crafting(t_data *data)
// {
// 	unsigned int	*pixel_ptr;
// 	unsigned int	*screen;
// 	int				i;
// 	int				j;

// 	pixel_ptr = (unsigned int *)data->textures[NORTH]->img->data;
// 	screen = (unsigned int *)data->screen->addr;
// 	i = -1;
// 	while (++i < TILE_SIZE)
// 	{
// 		j = -1;
// 		while (++j < TILE_SIZE)
// 		{
// 			screen[(i * data->screen->line_length / 4) + j] =
// 				pixel_ptr[(i * data->textures[NORTH]->line_len / 4) + j];
// 		}
// 	}
// }

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	y = y * 10 + 10;
	x = x * 10 + 10;
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			data->screen->data[((y + i) * data->screen->line_length / 4) + (x + j)] = color;
		}
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;
	t_viktor	offset;

	offset.x = (floor(data->player.x) - 7) * ((floor(data->player.x) - 7) > 0);
	offset.y = (floor(data->player.y) - 7) * ((floor(data->player.y) - 7) > 0);
	i = -1;
	while (++i < 14 && data->map[i + (int)offset.y])
	{
		j = -1;
		while (++j < 14 && data->map[i + (int)offset.y][j + (int)offset.x])
		{
			if (data->map[i + (int)offset.y][j + (int)offset.x] == '1')
				draw_square(data, j, i, 0xFF0000);
			else if (data->map[i + (int)offset.y][j + (int)offset.x] == '0')
				draw_square(data, j, i, 0x00FF00);
			else if (ft_strchr("NSEW", data->map[i + (int)offset.y][j + (int)offset.x]))
				draw_square(data, j, i, 0x0000FF);
		}
	}
}


// TODO: need to add the offset
void	minimapping(t_data *data)
{
	int		i;
	int		j;
	int		color;

	i = -1;
	while (++i < data->map_img->height)
	{
		j = -1;
		while (++j < data->map_img->width)
		{
			color = data->map_img->data[(i * data->map_img->line_len / 4) + j];
			data->screen->data[(i * data->screen->line_length / 4) + j] = color;
		}
	}
	draw_map(data);
}

void	calculate_img(t_data *data)
{
	int			i;
	double		cost;
	t_ray		ray;

	i = -1;
	cost = (double)FOV / (double)WIDTH;
	data->screen->data = (unsigned int *)data->screen->addr;
	while (++i < WIDTH / 2)
	{
		ray.angle = calculate_angle(data->player.angle,
			(cost * i), '-') * (M_PI / 180.0);
		ray.dist = calculate_dist(data, (data->player.angle - (cost * i)),
				ray.angle, &ray.nose);
		ray.angle = (data->player.angle - (cost * i)) * (M_PI / 180.0);
		// printf("angle: %f\n", ray.angle);
		put_texture(data, 719 - i, ray, -(cost * i));
		ray.angle = calculate_angle(data->player.angle,
			(cost * i), '+') * (M_PI / 180.0);
			ray.dist = calculate_dist(data, (data->player.angle + (cost * i)),
				ray.angle, &ray.nose);
		ray.angle = (data->player.angle + (cost * i)) * (M_PI / 180.0);
		// printf("angle: %f\n", ray.angle);
		put_texture(data, i + 720, ray, (cost * i));
	}
	minimapping(data);
	// exit(0);
}



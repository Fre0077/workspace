/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:54:08 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/10 22:05:18 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (ft_printe("Error\nFailed to create window\n"), 1);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, frame, data);
	return (0);
}

t_ft_img	*init_img(void)
{
	t_ft_img	*img;

	img = (t_ft_img *)ft_calloc(1, sizeof(t_ft_img));
	if (!img)
		return (ft_printe("Error\nFunction calloc failed\n"), NULL);
	img->img = NULL;
	img->path = NULL;
	img->width = -1;
	img->height = -1;
	return (img);
}

t_color	*init_color(void)
{
	t_color	*col;

	col = (t_color *)ft_calloc(1, sizeof(t_color));
	if (!col)
		return (ft_printe("Error\nFunction calloc failed\n"), NULL);
	col->color = NULL;
	col->red = -1;
	col->green = -1;
	col->blue = -1;
	return (col);
}

t_pkey	*init_pkey(void)
{
	t_pkey	*pkey;

	pkey = malloc(sizeof(t_pkey));
	pkey->dex = 0;
	pkey->six = 0;
	pkey->w = 0;
	pkey->a = 0;
	pkey->s = 0;
	pkey->d = 0;
	return (pkey);
}

void	init_minimap_texture(t_data *data)
{
	data->textures[4]->path = "head.xpm";
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (ft_printe("Error\nFunction calloc failed\n"), NULL);
	data->textures[0] = init_img();
	data->textures[1] = init_img();
	data->textures[2] = init_img();
	data->textures[3] = init_img();
	init_minimap_texture(data);
	data->map_img = init_img();
	data->map_img->path = ft_strdup("textures_xpm/map.xpm");
	data->screen = (t_screen *)ft_calloc(1, sizeof(t_screen));
	if (!data->screen)
		return (ft_printe("Error\nFunction calloc failed\n"), NULL);
	data->player = (t_viktor){0, 0, 0};
	data->f = init_color();
	data->c = init_color();
	data->pkey = init_pkey();
	data->mlx = mlx_init();
	data->map = NULL;
	data->move_speed = 25;
	data->mouse_speed = 0.2;
	data->mouse_x = WIDTH / 2;
	data->status = 0;
	return (data);
}

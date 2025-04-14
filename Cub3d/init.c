/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:54:08 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/14 17:40:11 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (!pkey)
		return (ft_printe("Error\nFunction malloc failed\n"), NULL);
	pkey->dex = 0;
	pkey->six = 0;
	pkey->f3 = 0;
	pkey->w = 0;
	pkey->a = 0;
	pkey->s = 0;
	pkey->d = 0;
	return (pkey);
}

void	init_texture(t_data *data)
{
	data->textures[0] = init_img();
	data->textures[1] = init_img();
	data->textures[2] = init_img();
	data->textures[3] = init_img();
	data->textures[4] = init_img();
	data->textures[4]->path = "textures_xpm/head.xpm";
	data->textures[5] = init_img();
	data->textures[5]->path = "textures_xpm/furnace_top.xpm";
	data->textures[6] = init_img();
	data->textures[6]->path = "textures_xpm/hardened_clay_stained_gray.xpm";
	data->textures[7] = init_img();
	data->textures[7]->path = "textures_xpm/door_spruce_lower.xpm";
	data->textures[8] = init_img();
	data->textures[8]->path = "textures_xpm/map.xpm";
	data->hand = init_img();
	data->hand->path = "textures_xpm/hand.xpm";
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (ft_printe("Error\nFunction calloc failed\n"), NULL);
	init_texture(data);
	data->frames = ft_strdup("");
	data->screen = (t_screen *)ft_calloc(1, sizeof(t_screen));
	if (!data->screen)
		return (ft_printe("Error\nFunction calloc failed\n"), NULL);
	data->player = (t_viktor){0, 0, 0};
	data->pos = (t_viktor){0, 0, 0};
	data->tmp = (t_viktor){0, 0, 0};
	data->f = init_color();
	data->c = init_color();
	data->pkey = init_pkey();
	data->mlx = mlx_init();
	data->map = NULL;
	data->zone_map = NULL;
	data->move_speed = 25;
	data->mouse_speed = 0.2;
	data->status = 0;
	return (data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:54:08 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/04 12:39:58 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ft_img	*init_img()
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



t_color	*init_color()
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

t_data	*init_data()
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (ft_printe("Error\nFunction calloc failed\n"), NULL);
	data->no = init_img();
	data->so = init_img();
	data->ea = init_img();
	data->we = init_img();
	data->f = init_color();
	data->c = init_color();
	data->map = NULL;
	data->mlx = mlx_init();
	data->player = (t_viktor){0, 0, 0};	//TODO: initialize player position after map parsing
	data->status = 0;
	data->screen = (t_screen *)ft_calloc(1, sizeof(t_screen));
	if (!data->screen)
		return (ft_printe("Error\nFunction calloc failed\n"), NULL);
	return (data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:18:45 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/15 11:01:00 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(t_ft_img *img, void *mlx, int i)
{
	if (!img)
		return ;
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	if (img->path && i < 4)
		free(img->path);
	free(img);
}

void	free_color(t_color *col)
{
	if (!col)
		return ;
	if (col->color)
		free(col->color);
	free(col);
}

void	free_data(t_data *data)
{
	if (data->mlx)
		free(data->mlx);
	if (data->screen)
		free(data->screen);
	if (data->pkey)
		free(data->pkey);
	if (data->frames)
		free(data->frames);
	if (data->f)
		free_color(data->f);
	if (data->c)
		free_color(data->c);
	if (data->map)
		ft_free_mat_char(data->map);
	if (data->zone_map)
		ft_free_mat_char(data->zone_map);
}

int	ft_close(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < 9)
	{
		if (data->textures[i])
			free_img(data->textures[i], data->mlx, i);
		i++;
	}
	if (data->hand)
		free_img(data->hand, data->mlx, 8);
	if (data->screen && data->screen->img)
		mlx_destroy_image(data->mlx, data->screen->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free_data(data);
	status = data->status;
	free(data);
	exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:18:45 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/04 12:39:58 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(t_ft_img *img, void *mlx)
{
	if (!img)
		return ;
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	if (img->path)
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

int	ft_close(t_data *data)
{
	int	status;

	free_img(data->no, data->mlx);
	free_img(data->so, data->mlx);
	free_img(data->ea, data->mlx);
	free_img(data->we, data->mlx);
	free_color(data->f);
	free_color(data->c);
	ft_free_mat_char(data->map);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	status = data->status;
	free(data);
	exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:48 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/10 16:18:35 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	camera_update(t_data *data)
{
	if (data->pkey->six)
		data->player.angle -= 0.6;
	if (data->pkey->dex)
		data->player.angle += 0.6;
	if (data->player.angle >= 360)
		data->player.angle -= 360;
	if (data->player.angle < 0)
		data->player.angle += 360;
}

void	move_update(t_data *data, double angle)
{
	t_viktor	prev;

	prev = data->player;
	if (data->pkey->w)
		data->player.y += sin(angle * (M_PI / 180.0)) / data->move_speed;
	if (data->pkey->w)
		data->player.x += cos(angle * (M_PI / 180.0)) / data->move_speed;
	if (data->pkey->a)
		data->player.y -= cos(angle * (M_PI / 180.0)) / data->move_speed;
	if (data->pkey->a)
		data->player.x += sin(angle * (M_PI / 180.0)) / data->move_speed;
	if (data->pkey->s)
		data->player.y -= sin(angle * (M_PI / 180.0)) / data->move_speed;
	if (data->pkey->s)
		data->player.x -= cos(angle * (M_PI / 180.0)) / data->move_speed;
	if (data->pkey->d)
		data->player.y += cos(angle * (M_PI / 180.0)) / data->move_speed;
	if (data->pkey->d)
		data->player.x -= sin(angle * (M_PI / 180.0)) / data->move_speed;
	check_move(prev, data);
}

void	check_move(t_viktor prev, t_data *data)
{
	if (hit(data, (t_viktor){data->player.x, prev.y, 0}))
		data->player.x = prev.x;
	if (hit(data, (t_viktor){prev.x, data->player.y, 0}))
		data->player.y = prev.y;
	if (data->pkey->w + data->pkey->a + data->pkey->s + data->pkey->d == 2)
	{
		data->player.x -= (data->player.x - prev.x) / 2;
		data->player.y -= (data->player.y - prev.y) / 2;
	}
}

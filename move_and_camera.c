/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:48 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/07 18:56:33 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == XK_Escape)
		ft_close(data);
	else if (key == XK_Left)
		data->pkey->six = 1;
	else if (key == XK_Right)
		data->pkey->dex = 1;
	else if (key == XK_w)
		data->pkey->w = 1;
	else if (key == XK_a)
		data->pkey->a = 1;
	else if (key == XK_s)
		data->pkey->s = 1;
	else if (key == XK_d)
		data->pkey->d = 1;
	else if (key == XK_Shift_L)
		data->move_speed = 25;
	if (key == XK_p)
		if (data->mouse_speed < 0.8)
			data->mouse_speed = data->mouse_speed * 2;
	if (key == XK_m)
		if(data->mouse_speed > 0.05)
			data->mouse_speed = data->mouse_speed / 2;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == XK_Left)
		data->pkey->six = 0;
	else if (key == XK_Right)
		data->pkey->dex = 0;
	else if (key == XK_w)
		data->pkey->w = 0;
	else if (key == XK_a)
		data->pkey->a = 0;
	else if (key == XK_s)
		data->pkey->s = 0;
	else if (key == XK_d)
		data->pkey->d = 0;
	else if (key == XK_Shift_L)
		data->move_speed = 80;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;
	double	change;

	change = data->mouse_speed * ((abs(x - data->mouse_x) / 5) + 1);	
	if (x > data->mouse_x)
		data->player.angle += change;
	else if (data->mouse_x > x)
		data->player.angle -= change;
	if (data->player.angle >= 360)
		data->player.angle -= 360;
	if (data->player.angle < 0)
		data->player.angle += 360;
	mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

void	camera_update(t_data *data)
{
	if (data->pkey->six)
		data->player.angle -= 0.75;
	else if (data->pkey->dex)
		data->player.angle += 0.75;
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
	if (hit(data, (t_viktor){data->player.x, prev.y, 0}))
		data->player.x = prev.x;
	if (hit(data, (t_viktor){prev.x, data->player.y, 0}))
		data->player.y = prev.y;
}

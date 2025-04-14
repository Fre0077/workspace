/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:28:08 by fde-sant          #+#    #+#             */
/*   Updated: 2025/04/14 17:40:11 by alborghi         ###   ########.fr       */
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
		data->move_speed = 10;
	if (key == XK_p)
		if (data->mouse_speed < 0.8)
			data->mouse_speed = data->mouse_speed * 2;
	if (key == XK_m)
		if (data->mouse_speed > 0.05)
			data->mouse_speed = data->mouse_speed / 2;
	if (key == XK_space)
		open_door(data);
	return (key_press_2(key, data));
}

int	key_press_2(int key, t_data *data)
{
	if (key == XK_F3 && !data->pkey->f3)
		data->pkey->f3 = 1;
	else if (key == XK_F3 && data->pkey->f3)
		data->pkey->f3 = 0;
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
		data->move_speed = 25;
	return (0);
}

int	mouse_click(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 3)
		open_door(data);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	double	change;

	change = data->mouse_speed * ((abs(x - WIDTH / 2) / 5) + 1);
	if (x > WIDTH / 2)
		data->player.angle += change;
	else if (WIDTH / 2 > x)
		data->player.angle -= change;
	if (x != WIDTH / 2 || y != HEIGHT / 2)
		mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

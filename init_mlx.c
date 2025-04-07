/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:48 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/07 15:33:54 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "X11/keysymdef.h"
#include "X11/keysym.h"

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
	return (0);
}

void	camera_update(t_data *data)
{
	if (data->pkey->six)
		data->player.angle -= 0.5;
	else if (data->pkey->dex)
		data->player.angle += 0.5;
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
		data->player.y += sin(angle * (M_PI / 180.0)) / MOVE_SPEED;
	if (data->pkey->w)
		data->player.x += cos(angle * (M_PI / 180.0)) / MOVE_SPEED;
	if (data->pkey->a)
		data->player.y -= cos(angle * (M_PI / 180.0)) / MOVE_SPEED;
	if (data->pkey->a)
		data->player.x += sin(angle * (M_PI / 180.0)) / MOVE_SPEED;
	if (data->pkey->s)
		data->player.y -= sin(angle * (M_PI / 180.0)) / MOVE_SPEED;
	if (data->pkey->s)
		data->player.x -= cos(angle * (M_PI / 180.0)) / MOVE_SPEED;
	if (data->pkey->d)
		data->player.y += cos(angle * (M_PI / 180.0)) / MOVE_SPEED;
	if (data->pkey->d)
		data->player.x -= sin(angle * (M_PI / 180.0)) / MOVE_SPEED;
	if (hit(data, (t_viktor){data->player.x, prev.y, 0}))
		data->player.x = prev.x;
	if (hit(data, (t_viktor){prev.x, data->player.y, 0}))
		data->player.y = prev.y;
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;
	double	change;

	change = MOUSE_SPEED * ((abs(x - data->mouse_x) / 5) + 1);	
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

// void calculate_img(t_data *data)
// {
//     int map_y;
//     int map_x;
//     int pixel_y;
//     int pixel_x;

// 	map_y = 0;
//     while (data->map[map_y])
//     {
//         map_x = 0;
//         while (data->map[map_y][map_x] != '\n' && data->map[map_y][map_x] != '\0')
//         {
//             unsigned int color;
//             if (data->map[map_y][map_x] == '1')

//                 color = 0xFFFFFF;
//             else if (data->map[map_y][map_x] == '0')
//                 color = 0x000000;
// 			else if (ft_strchr("NSWE", data->map[map_y][map_x]))
// 				color = 0x00FF00;
//             else
//                 color = 0xFF0000;

//             pixel_y = 0;
//             while (pixel_y < 16)
//             {
//                 pixel_x = 0;
//                 while (pixel_x < 16)
//                 {
//                     int screen_y = (map_y * 16) + pixel_y;
//                     int screen_x = (map_x * 16) + pixel_x;
//                     if (screen_y < HEIGHT && screen_x < WIDTH)
//                     {
                        // *(unsigned int *)(data->screen->addr + 
//                             (screen_y * data->screen->line_length) + 
//                             (screen_x * (data->screen->bpp / 8))) = color;
//                     }
//                     pixel_x++;
//                 }
//                 pixel_y++;
//             }
//             map_x++;
//         }
//         map_y++;
//     }
// }

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
		&data->screen->bpp, &data->screen->line_length, &data->screen->endian);
	if (!data->screen->addr)
		return (ft_printe("Error\nFailed to get data address\n"), 1);
	calculate_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen->img, 0, 0);
	return (0);
}

int	init_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (ft_printe("Error\nFailed to create window\n"), 1);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_hook(data->win, 2, 1L<<0, key_press, data);
	mlx_hook(data->win, 3, 1L<<1, key_release, data);
	mlx_hook(data->win, 6, 1L<<6, mouse_move, data);
	mlx_loop_hook(data->mlx, frame, data);
	return (0);
}

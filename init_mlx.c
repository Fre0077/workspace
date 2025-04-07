/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:48 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/06 21:00:45 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == 65307)
		ft_close(data);
	else if (key == 65361)
		data->player.angle--;
	else if (key == 65363)
		data->player.angle++;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)y;  // Ignora la posizione verticale del mouse

	if (data->mouse_x == -1)
		data->mouse_x = x - 1;
	if (x - data->mouse_x > WIDTH / 360)
	{
		data->player.angle++;
		data->mouse_x = x;
	}
	else if (data->mouse_x - x > WIDTH / 360)
	{
		data->player.angle--;
		data->mouse_x = x;
	}
	if (data->player.angle >= 360)
		data->player.angle -= 360;
	if (data->player.angle < 0)
		data->player.angle += 360;
	return (0);
}

//int	key_release(int key, t_data *data)
//{
//	ft_printf("cavolo %d\n", key);
//	if (key == 65361)
//		data->six = 0;
//	else if (key == 65363)
//		data->dex = 0;
//	return (0);
//}

//int	move_update(t_data *data)
//{
//	if (data->six)
//		data->player.angle -= 1;
//	else if (data->dex)
//		data->player.angle += 1;
//	return (0);
//}

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
	// sleep(20);
	// ft_close(data);
	return (0);
}

int	init_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (ft_printe("Error\nFailed to create window\n"), 1);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(data->win, 6, 1L<<6, mouse_move, data);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_hook(data->win, 2, 1L<<0, key_press, data);
	//mlx_loop_hook(data->mlx, move_update, data);
	mlx_loop_hook(data->mlx, frame, data);
	return (0);
}

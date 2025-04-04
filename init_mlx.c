/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:48 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/04 17:33:26 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		ft_close(data);
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
//                         *(unsigned int *)(data->screen->addr + 
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
	// ft_close(data);
	return (0);
}

int	init_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (ft_printe("Error\nFailed to create window\n"), 1);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_loop_hook(data->mlx, frame, data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:33:04 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/14 17:40:11 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// mlx_mouse_hide(data->mlx, data->win);
int	init_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (ft_printe("Error\nFailed to create window\n"), 1);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_click, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, frame, data);
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_ms);
}

void	print_f3(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 180, 20, 0xFFFFFF,
		"Minecraft X Wolfestein 3D: beta 0.69427");
	mlx_string_put(data->mlx, data->win, 180, 60, 0xFFFFFF,
		"FPS:");
	mlx_string_put(data->mlx, data->win, 209,
		60, 0xFFFFFF, data->frames);
	mlx_string_put(data->mlx, data->win, 180, 80, 0xFFFFFF,
		"Biome: Wakanda (c1r6p7)");
	mlx_string_put(data->mlx, data->win, 180, 100, 0xFFFFFF,
		"Graphic card: NVIDIA GeForce GTX 1650");
	mlx_string_put(data->mlx, data->win, 180, 120, 0xFFFFFF,
		"Display info: 1440 X 900");
	mlx_string_put(data->mlx, data->win, 180, 140, 0xFFFFFF,
		"Sound: Work in progress...");
	mlx_string_put(data->mlx, data->win, 180, 160, 0xFFFFFF,
		"Dimension: Cub3D");
}

void	frame_counter(t_data *data)
{
	char	*tmp;

	data->time = get_time();
	if (data->pkey->f3)
	{
		tmp = ft_strjoin_free_2("X: ",
				ft_strjoin_free_1_2(ft_itoa(data->player.x),
					ft_strjoin_free_2(" / Y: ", ft_itoa(data->player.y))));
		mlx_string_put(data->mlx, data->win, 180, 40, 0xFFFFFF, tmp);
		free(tmp);
		print_f3(data);
	}
	if (data->time >= data->frame_time + 1000)
	{
		free(data->frames);
		data->frames = NULL;
		data->frames = ft_itoa(data->frame);
		data->frame = 0;
		data->frame_time = data->time;
	}
}

// - 42 - 6 = -48 = - '0'
int	safe_atoi(char *s)
{
	int	i;
	int	n;

	if (ft_strlen_int(s) > 3 || !s)
		return (-1);
	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			return (-1);
	n = ft_atoi(s);
	if (n > 255)
		return (-1);
	return (n);
}
//pere per c******a
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:42:48 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/02 17:58:48 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		ft_close(data);
	return (0);
}

int	init_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (ft_printe("Error\nFailed to create window\n"), 1);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_key_hook(data->win, key_hook, data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:17:23 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/03 18:14:12 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (1);
	}
	data = init_data();
	if (init_mlx(data) == 1)
		return (ft_close(data));
	if (parsing(data, argv[1]) == 1)
		ft_close(data);
	print_data(data);
	mlx_loop(data->mlx);
	return (0);
}

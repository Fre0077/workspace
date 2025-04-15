/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:17:23 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/15 10:21:42 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_printe("Error\nWrong number of arguments\n", 2), 1);
	data = init_data();
	if (read_file(argv[1], data))
		ft_close(data);
	if (parsing(data) == 1)
		ft_close(data);
	if (init_mlx(data) == 1)
		ft_close(data);
	mlx_loop(data->mlx);
	return (0);
}

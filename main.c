/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:17:23 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/02 18:58:53 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_map(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
	{
		ft_putstr_fd(mat[i], 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printe("Error\nFailed to initialize mlx\n"), 1);
	if (parsing(&data, argv[1]) == 1)
		ft_close(&data);
	ft_put_map(data.map);
	init_mlx(&data);
	mlx_loop(data.mlx);
	return (0);
}

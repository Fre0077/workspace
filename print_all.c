/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:15:55 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/04 15:00:12 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_img(t_ft_img *img)
{
	ft_printf("Image path: %s\n", img->path);
	ft_printf("Image width: %d\n", img->width);
	ft_printf("Image height: %d\n", img->height);
	ft_printf("Image pointer: %p\n", img->img);
}

void	print_color(t_color *col)
{
	ft_printf("Color string: %s\n", col->color);
	ft_printf("Red: %d\n", col->red);
	ft_printf("Green: %d\n", col->green);
	ft_printf("Blue: %d\n", col->blue);
}

void	print_map(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
	{
		ft_printf("%s\n", mat[i]);
		i++;
	}
}

void	print_data(t_data *data)
{
	ft_printf("North texture:\n");
	print_img(data->no);
	ft_printf("\nSouth texture:\n");
	print_img(data->so);
	ft_printf("\nEast texture:\n");
	print_img(data->ea);
	ft_printf("\nWest texture:\n");
	print_img(data->we);
	ft_printf("\nFloor color:\n");
	print_color(data->f);
	ft_printf("\nCeiling color:\n");
	print_color(data->c);
	ft_printf("\nMap:\n");
	print_map(data->map);
}
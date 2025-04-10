/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:31:09 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/10 14:21:59 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	load_colors(t_data *data)
{
	char	**split;

	split = ft_split(data->f->color, ',');
	if (!split || ft_char_mat_len(split) != 3)
		return (ft_printe("Error\nInvalid floor color\n"), 1);
	data->f->red = safe_atoi(split[0]);
	data->f->green = safe_atoi(split[1]);
	data->f->blue = safe_atoi(split[2]);
	if (data->f->red == -1 || data->f->green == -1 || data->f->blue == -1)
		return (ft_printe("Error\nInvalid floor color\n"), 1);
	ft_free_mat_char(split);
	split = ft_split(data->c->color, ',');
	if (!split || ft_char_mat_len(split) != 3)
		return (ft_printe("Error\nInvalid ceiling color\n"), 1);
	data->c->red = safe_atoi(split[0]);
	data->c->green = safe_atoi(split[1]);
	data->c->blue = safe_atoi(split[2]);
	if (data->c->red == -1 || data->c->green == -1 || data->c->blue == -1)
		return (ft_printe("Error\nInvalid ceiling color\n"), 1);
	ft_free_mat_char(split);
	return (0);
}

void ft_put_img_data(t_ft_img *img, int max_pixels) 
{
    int i;
    unsigned int *pixel_ptr;
    
    if (!img || !img->img || !img->img->data)
        return;
        
    printf("\nTexture %s (%dx%d) pixel data:\n", 
			img->path, img->width, img->height);
    
    pixel_ptr = (unsigned int *)img->img->data;
    for (i = 0; i < max_pixels && i < (img->width * img->height); i++) {
        printf(" 0x%06X ", pixel_ptr[i]);
        if ((i + 1) % TILE_SIZE == 0) 
            printf("\n");
    }
    printf("\n");
}

int	mlx_fa_schifo(t_data *data, int	side)
{
	data->textures[side]->img = mlx_xpm_file_to_image(data->mlx,
		data->textures[side]->path,
			&data->textures[side]->width, &data->textures[side]->height);
	if (!data->textures[side]->img)
		return (1);
	data->textures[side]->img->data = mlx_get_data_addr(
		data->textures[side]->img,
		&data->textures[side]->bpp,
		&data->textures[side]->line_len,
		&data->textures[side]->endian);
	// ft_put_img_data(data->textures[side], TILE_SIZE * TILE_SIZE);
	if (!data->textures[side]->img->data)
		return (1);
	data->textures[side]->data =
		(unsigned int *)data->textures[side]->img->data;
	return (0);
}

int	load_textures(t_data *data)
{
	if (mlx_fa_schifo(data, EAST))
		return (ft_printe("Error\nInvalid east texture\n"), 1);
	if (mlx_fa_schifo(data, SOUTH))
		return (ft_printe("Error\nInvalid south texture\n"), 1);
	if (mlx_fa_schifo(data, WEST))
		return (ft_printe("Error\nInvalid west texture\n"), 1);
	if (mlx_fa_schifo(data, NORTH))
		return (ft_printe("Error\nInvalid north texture\n"), 1);
	return (0);
}

void	find_player(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (ft_strchr("NSWE", data->map[i][j]))
			{
				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
				if (data->map[i][j] == 'N')
					data->player.angle = 270;
				else if (data->map[i][j] == 'S')
					data->player.angle = 90;
				else if (data->map[i][j] == 'E')
					data->player.angle = 0;
				else if (data->map[i][j] == 'W')
					data->player.angle = 180;
				return ;
			}
		}
	}
}

int	parsing(t_data *data)
{
	if (!data->f->color || !data->c->color)
		return (ft_printe("Error\nMissing color\n"), 1);
	if (!data->textures[EAST]->path || !data->textures[SOUTH]->path
		|| !data->textures[WEST]->path || !data->textures[NORTH]->path)
		return (ft_printe("Error\nMissing texture path\n"), 1);
	if (!data->map)
		return (ft_printe("Error\nMissing map\n"), 1);
	if (load_colors(data))
		return (ft_printe("Error\nInvalid color\n"), 1);
	if (load_textures(data))
		return (ft_printe("Error\nInvalid texture\n"), 1);
	find_player(data);
	return (0);
}

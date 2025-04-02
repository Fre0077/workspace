/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:17:36 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/02 18:34:03 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "my_libft/my_include.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>

# define WIDTH 1440
# define HEIGHT 900

typedef struct s_img
{
	void	*img;
	char	*path;
	int		width;
	int		height;
}			t_img;

typedef struct s_color
{
	char	*color;
	int		red;
	int		green;
	int		blue;
}			t_color;

typedef struct s_data
{
	char	**map;
	t_img	*no;
	t_img	*so;
	t_img	*ea;
	t_img	*we;
	t_color	*f;
	t_color	*c;
	void	*mlx;
	void	*win;
	int		status;
}			t_data;

// read_file.c
/**
 * @brief Parse the file and fill the data structure
 * @param file The file to parse
 * @param data The data structure to fill
 * @return 0 if the file is parsed correctly, 1 otherwise
 */
int		read_file(char *file, t_data *data);
/**
 * @brief Check if the file has the right extension and if it exists
 * @param file The file to check
 * @return 0 if the file is correct, 1 otherwise
 * @note The file must have the extension ".cub"
 * @note The function prints an error message if the file is not correct
 */
int		check_file(char *file);

// parsing.c
int		parsing(t_data *data, char *file);

// init_mlx.c
int		init_mlx(t_data *data);

// exit.c
int	ft_close(t_data *data);

#endif
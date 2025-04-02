/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:17:36 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/02 16:43:14 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "my_libft/my_include.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>

typedef struct s_data
{
	char	**map;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*f;
	char	*c;
}			t_data;

// parsing.c
/**
 * @brief Parse the file and fill the data structure
 * @param file The file to parse
 * @param data The data structure to fill
 * @return 0 if the file is parsed correctly, 1 otherwise
 */
int		parse_file(char *file, t_data *data);

/**
 * @brief Check if the file has the right extension and if it exists
 * @param file The file to check
 * @return 0 if the file is correct, 1 otherwise
 * @note The file must have the extension ".cub"
 * @note The function prints an error message if the file is not correct
 */
int		check_file(char *file);

#endif
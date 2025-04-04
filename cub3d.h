/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:17:36 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/04 18:18:34 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "my_libft/my_include.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 1440
# define HEIGHT 900
# define FOV 42 * 2
# define TILE_SIZE 128
# define M_PI 3.14159265358979323846

typedef struct s_viktor
{
	double	x;
	double	y;
	double	angle;
}			t_viktor;

typedef struct s_ft_img
{
	t_img	*img;
	char	*path;
	int		width;
	int		height;
}			t_ft_img;

typedef struct s_color
{
	char	*color;
	int		red;
	int		green;
	int		blue;
}			t_color;

typedef struct s_screen
{
	t_img	*img;
	char	*addr;
	int		line_length;
	int		endian;
	int		bpp;
}			t_screen;

typedef struct s_ray
{
	t_viktor	dir;
	t_viktor	plane;
}			t_ray;

typedef struct s_data
{
	char	**map;
	t_ft_img	*no;
	t_ft_img	*so;
	t_ft_img	*ea;
	t_ft_img	*we;
	t_color	*f;
	t_color	*c;
	void	*mlx;
	void	*win;
	int		status;
	t_screen	*screen;
	t_viktor	player;
	t_ray	ray;
}			t_data;

//dist_wall.c
int			hit(t_data *data, t_viktor tmp);
double		calculate_dist(t_data *data, double angle);
void		calculate_img(t_data *data);

// exit.c
void		free_img(t_ft_img *img, void *mlx);
void		free_color(t_color *col);
int			ft_close(t_data *data);

// init_mlx.c
int			key_hook(int keycode, t_data *data);
int			frame(void *arg);
int			init_mlx(t_data *data);

// init.c
t_ft_img	*init_img(void);
t_color		*init_color(void);
t_data		*init_data(void);

// parsing.c
int			safe_atoi(char *s);
int			load_colors(t_data *data);
int			load_textures(t_data * data);
int			parsing(t_data *data);

// print_all.c
void		print_img(t_ft_img *img);
void		print_color(t_color *col);
void		print_map(char **mat);
void		print_data(t_data *data);

// read_check.c
int			check_file(char *file);
int			check_player(t_data *data);
int			check_char(t_data *data);
int			check_auschwitz(t_data *data);

// read_file.c
int			allocate_texture_path(char *path, t_ft_img *img);
int			allocate_color(char *color, t_color *col);
int			process_line(char *line, t_data *data);
int			read_file(char *file, t_data *data);

/**
 * @brief Check if the file has the right extension and if it exists
 * @param file The file to check
 * @return 0 if the file is correct, 1 otherwise
 * @note The file must have the extension ".cub"
 * @note The function prints an error message if the file is not correct
 */
int			check_file(char *file);
/**
 * @brief alloca le path delle texture verificando che non siano doppie
 * @param path il path da allocare
 * @param img la struttura dove inserire il path
 * @return 0 se l'allocazione va a buon fine, 1 se c'e' un doppione
 * @note la funzione printa due differenti mesaggi di errore
 */
int			allocate_texture_path(char *path, t_ft_img *img);
/**
 * @brief alloca i colori verificando che non siano doppi
 * @param color il colore da allocare
 * @param col la struttura dove inserire il colore
 * @return 0 se l'allocazione va a buon fine, 1 se c'e' un doppione
 * @note la funzione printa due differenti mesaggi di errore
 */
int			allocate_color(char *color, t_color *col);
/**
 * @brief controlla riga per riga fino ad arrivare alla mappa
 * @param line la riga da controllare
 * @param data struct data generale
 * @return 0 se non ci sono errori, 1 in caso di errore, 2 se si e' raggiunta la mappa
 */
int			process_line(char *line, t_data *data);
/**
 * @brief controlla che ci sia solo un player
 * @param data struct data generale
 * @return 0 se non ci sono errori, oppure 1
 * @note la funzione printa due differenti mesaggi di errore
 */
int			check_player(t_data *data);
/**
 * @brief controlla non ci siano caratteri non validi
 * @param data struct data generale
 * @return 0 se non ci sono errori, oppure 1
 * @note la funzione printa un messaggio di errore
 */
int			check_char(t_data *data);
/**
 * @brief controlla che tutte le pareti siano chiuse
 * @param data struct data generale
 * @return 0 se non ci sono errori, oppure 1
 * @note la funzione printa un meffaggio di errore
 */
int			check_auschwitz(t_data *data);
/**
 * @brief Parse the file and fill the data structure
 * @param file The file to parse
 * @param data The data structure to fill
 * @return 0 if the file is parsed correctly, 1 otherwise
 */
int			read_file(char *file, t_data *data);

#endif
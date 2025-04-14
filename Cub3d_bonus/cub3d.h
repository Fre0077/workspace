/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:17:36 by alborghi          #+#    #+#             */
/*   Updated: 2025/04/14 18:19:26 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "my_libft/my_include.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "X11/keysymdef.h"
# include "X11/keysym.h"
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>

# define M_PI 3.14159265358979323846
# define RAD 0.017453293 // (M_PI / 180)
# define TILE_SIZE 128
# define WIDTH 1440
# define HEIGHT 900
# define FOV 66
# define MAP 140
# define C 0.045833333 // (FOV / WIDTH)

enum e_sides
{
	EAST,
	SOUTH,
	WEST,
	NORTH
};

typedef struct s_pkey
{
	int			dex;
	int			six;
	int			f3;
	int			w;
	int			a;
	int			s;
	int			d;
}				t_pkey;

typedef struct s_viktor
{
	double		x;
	double		y;
	double		angle;
}				t_viktor;

typedef struct s_ray
{
	t_viktor	nose;
	double		dist;
	double		angle;
	char		seen_block;
}				t_ray;

typedef struct s_color
{
	char		*color;
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct s_ft_img
{
	t_img			*img;
	char			*path;
	int				width;
	int				height;
	int				endian;
	int				bpp;
	int				line_len;
	unsigned int	*data;
}				t_ft_img;

typedef struct s_screen
{
	t_img			*img;
	char			*addr;
	unsigned int	*data;
	int				line_length;
	int				endian;
	int				bpp;
}				t_screen;

typedef struct s_data
{
	int			frame;
	long		time;
	long		frame_time;
	char		*frames;

	t_ft_img	*textures[9];
	t_ft_img	*hand;
	t_screen	*screen;
	t_viktor	player;
	t_viktor	pos;
	t_viktor	tmp;
	t_color		*f;
	t_color		*c;
	t_pkey		*pkey;
	t_ray		ray;
	void		*mlx;
	void		*win;
	char		seen_block;
	char		**zone_map;
	char		**map;
	double		mouse_speed;
	double		move_speed;
	int			status;
}				t_data;

//===============================================================
//check_file.c

int			check_file(char *file);
int			check_player(t_data *data);
int			check_char(t_data *data);
int			check_auschwitz(t_data *data);
int			map_checks(t_data *data);
//===============================================================
//dist_wall_utils.c

int			hit(t_data *data, t_viktor tmp);
double		r(double angle);
double		rad(double rad);
double		mult_of_90(double num, char direct);
double		calc_angle(double angle, double cost, char sign);
//===============================================================
//dist_wall.c

double		zero_case(t_data *data, t_viktor dir, double angle, t_ray *ray);
void		first_step(double dist[], t_viktor *tmp, t_viktor player,
				t_viktor dir);
double		calc_dist(t_data *data, double angle, t_ray *ray, t_viktor *tm);
//===============================================================
//dist_wallp.c

t_viktor	calc_distp(t_data *data, double angle, double ra);
t_viktor	zero_casep(t_data *data, t_viktor *tm, t_viktor dir, int witch);
void		first_stepp(double dist[], t_viktor *tmp, t_viktor player,
				t_viktor dir);
int			hitp(t_data *data, t_viktor tmp);
//===============================================================
// exit.c

void		free_img(t_ft_img *img, void *mlx, int i);
void		free_color(t_color *col);
void		free_data(t_data *data);
int			ft_close(t_data *data);
//===============================================================
// init.c

t_ft_img	*init_img(void);
t_color		*init_color(void);
t_pkey		*init_pkey(void);
void		init_texture(t_data *data);
t_data		*init_data(void);
//===============================================================
// key_and_mouse.c

int			key_press(int key, t_data *data);
int			key_press_2(int key, t_data *data);
int			key_release(int key, t_data *data);
int			mouse_click(int button, int x, int y, t_data *data);
int			mouse_move(int x, int y, t_data *data);
//===============================================================
// minimap.c

void		update_player_pos(t_data *data);
void		draw_head(t_data *data, int x, int y);
void		draw_div12(t_data *data, int x, int y, int f);
void		draw_map(t_data *data);
void		minimapping(t_data *data);
//===============================================================
// move_and_camera.c

void		open_door(t_data *data);
void		camera_update(t_data *data);
void		move_update(t_data *data, double angle);
void		check_move(t_viktor prev, t_data *data);
//===============================================================
// parsing.c

int			load_colors(t_data *data);
int			mlx_fa_schifo(t_ft_img *img, t_data *data);
int			load_textures(t_data *data);
void		find_player(t_data *data);
int			parsing(t_data *data);
//===============================================================
// print_all.c

void		print_img(t_ft_img *img);
void		print_color(t_color *col);
void		print_map(char **mat);
void		print_data(t_data *data);
//===============================================================
// put_texture.c

int			side(t_data *data, t_ray ray);
int			get_wall_color(t_data *data, t_ray ray, int y, double ang[2]);
//================================================================
// read_file.c

int			allocate_texture_path(char *path, t_ft_img *img);
int			allocate_color(char *color, t_color *col);
int			process_line(char *line, t_data *data);
int			read_map(char *line, t_data *data, int fd);
int			read_file(char *file, t_data *data);
//===============================================================
//rendering.c

int			init_mlx(t_data *data);
int			frame(void *arg);
void		pointer(t_data *data);
void		put_texture(t_data *data, int i, t_ray ray, double corr_angle);
void		calculate_img(t_data *data, double cost);
//===============================================================
//utils.c

int			init_mlx(t_data *data);
long		get_time(void);
void		print_f3(t_data *data);
void		frame_counter(t_data *data);
int			safe_atoi(char *s);
//===============================================================

/**
 * @brief controlla se il file ha la giusta estensione e se esiste
 * @param file il file da controllare
 * @return 0 se il file è corretto, 1oppure 1
 * @note il file deve essere un ".cub"
 * @note la funzione printa un messaggio di errore
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
 * @return 0 se non ci sono errori, 1 in caso di errore, 2 se si e' 
 * raggiunta la mappa
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
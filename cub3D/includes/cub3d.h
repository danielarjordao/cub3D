/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:14:08 by dramos-j          #+#    #+#             */
/*   Updated: 2025/04/03 18:46:14 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/include/libft.h"
# include "../lib/minilibx/mlx.h"
# include <math.h>

/* ******************************* STRUCTS ********************************** */


typedef struct s_map
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	**map;
	int		floor_color[3];
	int		ceiling_color[3];
	int		floor_color_hex;
	int		ceiling_color_hex;
	int		map_width;
	int		map_height;
	double		player_x;
	double		player_y;
	char	player_dir;
	double	player_dir_x;
	double	player_dir_y;
	double	camera_x;
	double	camera_y;
}	t_map;

typedef struct s_mlx
{
	void	*connection;
	void	*win;
	void	*img_to_render;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_textures
{
	char	*img;
	int		bpp;
	int		size_line;
	int		endian;
}	t_textures;


typedef struct s_ray
{
	int		raycaster;
	double	dir_x;
	double	dir_y;
	double	length_per_x_unity;
	double	length_per_y_unity;
	double	magnitude_crossing_x;
	double	magnitude_crossing_y;
	double	perpWallDist;
	int	step_x;
	int	step_y;
	int	x_grid;
	int	y_grid;
	int	wall_height;
	int	hit_grid;
}	t_ray;

/* ******************************* DEFINES ********************************** */

typedef struct s_game
{
	t_map		*map;
	t_mlx		*mlx;
	t_textures	*textures;
	t_mem_alloc	mem_alloc;
	t_ray		ray;
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left_arrow;
	int			key_right_arrow;
}	t_game;

# define SCREEN_WIDTH 1800
# define SCREEN_HEIGHT 900
# define CAMERA_MAGNITUDE 0.66
# define NONE 0
# define VERTICAL 1
# define HORIZONTAL 2
# define DELTA_MOV 0.1
# define ROTATE_ANGLE 10
# define TEXTURE_WIDTH 256
# define TEXTURE_HEIGHT 256

typedef enum msg_error
{
	MALLOC_FAIL,
	W_NBR_ARGS,
	INVALID_EXT,
	OPEN_FAIL,
	TEX_OPEN_FAIL,
	TEX_INVALID_EXT,
	TEX_PATH_DUP,
	COL_FORMAT_ERR,
	COL_DUPLICATE,
	MISSING_INFO,
	MAP_FORMAT_ERR,
	MAP_INVALID_CHAR
}	t_error;

/* ******************************* INIT_FUNCTIONS *********************************** */

/* init_data.c */
bool	init_map(t_map **map);
void	init_game(t_game *game);
void	init_mlx(t_game *game);
void	init_textures(t_game *game);
void	init_raycasting(t_game *game);

/* ******************************** PARSE *********************************** */

/* parse.c */
bool	parse(char *file, t_map **map);
bool	is_valid_extension(char *file, char *ext);
bool	is_content_valid(int fd, t_map **map);
bool	is_line_valid(char *line, t_map **map);

/* parse_textures.c */
bool	is_texture_valid(char *line, t_map **map);
bool	is_path_valid(char *line, char c, t_map **map);
bool	add_texture(char *line, char c, t_map **map);

/* parse_colors.c */
bool	is_color_valid(char *line, t_map **map);
bool	add_color(char **temp, int *color, t_map **map);
bool	add_color(char **temp, int *color, t_map **map);
bool	valid_number_format(char *str);
void	convert_rgb_to_hex(int *color, t_map **map);
void	convert_rgb_to_hex(int *color, t_map **map);

/* parse_map.c */
bool	is_map_valid(char *line, t_map **map);
bool	are_colors_and_textures_set(t_map **map);
bool	are_colors_and_textures_set(t_map **map);
void	add_map_line(char *line, t_map **map);

/* parse_utils.c */
int		ignore_spaces(char *line);
bool	is_empty_line(char *line);
char	*ft_trim_spaces(char *line);

void	print_map(t_map *map);

/* ******************************** GAME ************************************ */

/* start_game.c */
void	start_game(t_game *game);

/* handle_events.c */
void	handle_events(t_game *game);

/* ****************************** RAYCASTING ******************************** */

/* raycasting.c */
void	raycasting(t_game *game);

/* render.c */
void	render(t_game *game, int x_screen, int wall_height);


/* ******************************* UTILS *********************************** */

/* check_mem.c */
void	check_mem(t_game *game, t_list **ptr_or_matrix_list, \
	void *ptr, char *error_msg);
void	destroy_free_exit_error(t_game *game, char *error_msg);
void	call_destroy_functions(t_game *game);
void	free_all(t_mem_alloc *mem_allocation);

/* free_mem.c */
void	free_mem(void);
void	free_map(t_map *map);

/* utils.c */
bool	msg_error(t_error err);
int	close_game(t_game *game);

#endif

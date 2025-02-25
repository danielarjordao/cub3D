/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:14:08 by dramos-j          #+#    #+#             */
/*   Updated: 2025/02/25 14:38:16 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/include/libft.h"
# include "../lib/minilibx/mlx.h"

/* ******************************* STRUCTS ********************************** */

typedef struct s_map
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_textures
{
	void	*no_texture;
	void	*so_texture;
	void	*we_texture;
	void	*ea_texture;
}	t_textures;

typedef struct s_ray
{
	int		raycaster;
}	t_ray;

/* ******************************* DEFINES ********************************** */

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
	COL_DUPLICATE
}	t_error;

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
bool	add_color(char *line, char c, t_map **map);

/* parse_map.c */
bool	is_map_valid(char *line, t_map **map);

/* parse_utils.c */
bool	is_space(char c);
int		ignore_spaces(char *line);
bool	is_empty_line(char *line);
char	*ft_trim_spaces(char *line);

void	print_map(t_map *map);

/* ******************************** GAME ************************************ */

/* start_game.c */
void	start_game(void);

/* handle_events.c */
void	handle_events(void);

/* ****************************** RAYCASTING ******************************** */

/* raycasting.c */
void	raycasting(void);

/* render.c */
void	render(void);

/* ******************************* UTILS *********************************** */

/* init_data.c */
bool	init_map(t_map **map);
void	init_mlx(void);
void	init_textures(void);
void	init_raycasting(void);

/* free_mem.c */
void	free_mem(void);
void	free_map(t_map *map);

/* utils.c */
bool	msg_error(t_error err);

#endif

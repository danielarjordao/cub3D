/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:14:08 by dramos-j          #+#    #+#             */
/*   Updated: 2025/02/27 11:00:16 by mde-souz         ###   ########.fr       */
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
	char	**map;
	int		floor_color[3];
	int		ceiling_color[3];
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_mlx
{
	void	*connection;
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

typedef struct s_game
{
	t_map		*map;
	t_mlx		*mlx;
	t_textures*	textures;
	t_mem_alloc	mem_alloc;
}	t_game;

typedef struct s_ray
{
	int		raycaster;
}	t_ray;

/* ******************************* DEFINES ********************************** */

typedef enum msg_error
{
	W_NBR_ARGS,
	W_EXTENSION
}	t_error;

# define SCREEN_WIDTH 1800
# define SCREEN_HEIGHT 900

/* ******************************* INIT_FUNCTIONS *********************************** */

/* init_data.c */
void	init_game(t_game *game);
void	init_map(void);

/* ******************************* PARSING ********************************** */

/* parsing.c */
void	parsing(char *file);

/* ******************************** GAME ************************************ */

/* start_game.c */
void	start_game(t_game *game);

/* handle_events.c */
void	handle_events(void);

/* ****************************** RAYCASTING ******************************** */

/* raycasting.c */
void	raycasting(void);

/* render.c */
void	render(void);


/* ******************************* UTILS *********************************** */

/* check_mem.c */
void	check_mem(t_game *game, t_list **ptr_or_matrix_list, \
	void *ptr, char *error_msg);
void	destroy_free_exit_error(t_game *game, char *error_msg);

/* free_mem.c */
void	free_mem(void);

/* utils.c */
int	msg_error(t_error err, int ret);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:14:08 by dramos-j          #+#    #+#             */
/*   Updated: 2025/02/02 17:37:59 by dramos-j         ###   ########.fr       */
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
	W_NBR_ARGS,
	W_EXTENSION
}	t_error;

/* ******************************* PARSING ********************************** */

/* parsing.c */
void	parsing(char *file);

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
void	init_map(void);
void	init_mlx(void);
void	init_textures(void);
void	init_raycasting(void);

/* free_mem.c */
void	free_mem(void);

/* utils.c */
int	msg_error(t_error err, int ret);

#endif

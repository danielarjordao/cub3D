/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:46:40 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:46:41 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	init_map(t_map **map)
{
	//REVIEW -> Trocar para calloc
	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
		return (msg_error(MALLOC_FAIL));
	(*map)->no_texture = NULL;
	(*map)->so_texture = NULL;
	(*map)->we_texture = NULL;
	(*map)->ea_texture = NULL;
	(*map)->map = NULL;
	(*map)->map_width = 0;
	(*map)->map_height = 0;
	(*map)->player_x = 0.0;
	(*map)->player_y = 0.0;
	(*map)->player_dir = 0;
	(*map)->floor_color[0] = -1;
	(*map)->floor_color[1] = -1;
	(*map)->floor_color[2] = -1;
	(*map)->ceiling_color[0] = -1;
	(*map)->ceiling_color[1] = -1;
	(*map)->ceiling_color[2] = -1;
	return (true);
}

//leak checked
void	init_variables_game(t_game *game)
{
	errno = 0;
	game->mem_alloc.ptr_mem_list = NULL;
	game->mem_alloc.matrix_mem_list = NULL;
	game->textures[NO].img = NULL;
	game->textures[SO].img = NULL;
	game->textures[EA].img = NULL;
	game->textures[WE].img = NULL;
	game->gun.img = NULL;
	game->gun_fire.img = NULL;
	game->mlx = ft_calloc(1, sizeof(t_mlx));
	check_mem(game, &(game->mem_alloc.ptr_mem_list), \
		game->mlx, "ft_calloc for connection failed");
	game->mlx->connection = NULL;
	game->mlx->win = NULL;
	game->mlx->img_to_render = NULL;
	game->mlx->addr = NULL;
	game->key_w = FALSE;
	game->key_a = FALSE;
	game->key_s = FALSE;
	game->key_d = FALSE;
	game->key_left_arrow = FALSE;
	game->key_right_arrow = FALSE;
	game->shooting = FALSE;
	game->delta_x_mouse = 0;
}

//leak checked
void	init_mlx(t_game *game)
{
	game->mlx->connection = mlx_init();
	check_mem(game, &(game->mem_alloc.ptr_mem_list), \
			game->mlx->connection, "Mlx_init failed");
	game->mlx->win = mlx_new_window(game->mlx->connection, SCREEN_WIDTH, \
		SCREEN_HEIGHT, "Cub3D");
	if (!(game->mlx->win))
		destroy_free_exit_error(game, "mlx_new_window failed");
	game->mlx->img_to_render = mlx_new_image(game->mlx->connection, \
		SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!(game->mlx->img_to_render))
		destroy_free_exit_error(game, "mlx_new_image failed");
	game->mlx->addr = mlx_get_data_addr(game->mlx->img_to_render, \
		&(game->mlx->bpp), &(game->mlx->size_line), &(game->mlx->endian));
	if (!(game->mlx->addr))
		destroy_free_exit_error(game, "mlx_get_data_addr failed");
}

//leak checked
void	init_textures(t_game *game)
{
	xpm_to_image(game, &game->textures[NO], game->map->no_texture);
	xpm_to_image(game, &game->textures[SO], game->map->so_texture);
	xpm_to_image(game, &game->textures[EA], game->map->ea_texture);
	xpm_to_image(game, &game->textures[WE], game->map->we_texture);
	xpm_to_image(game, &game->gun, "textures/gun1.xpm");
	xpm_to_image(game, &game->gun_fire, "textures/gun2.xpm");
	if (game->textures[NO].img == NULL || game->textures[SO].img == NULL \
		|| game->textures[EA].img == NULL || game->textures[WE].img == NULL \
		|| game->gun.img == NULL || game->gun_fire.img == NULL)
		destroy_free_exit_error(game, "mlx_xpm_file_to_image failed");
}

void	init_game(t_game *game)
{
	init_variables_game(game);
	init_mlx(game);
	init_textures(game);
	init_raycasting(game);
}

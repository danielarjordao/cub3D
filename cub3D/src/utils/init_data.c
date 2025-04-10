#include "../../includes/cub3d.h"

bool	init_map(t_map **map)
{
	//REVIEW -> Trocar para calloc
	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
		return (MALLOC_FAIL);
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

void	init_variables_game(t_game *game)
{
	errno = 0;
	game->mem_alloc.ptr_mem_list = NULL;
	game->mem_alloc.matrix_mem_list = NULL;
	game->mlx = ft_calloc(1, sizeof(t_mlx));
	//REVIEW - TESTAR SE FALHAR
	check_mem(game, &(game->mem_alloc.ptr_mem_list), game->mlx, "ft_calloc failed");
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
}

void	init_mlx(t_game *game)
{
	ft_printf(1, "		Initializing mlx\n");
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
	//REVIEW -> memoria verificada ate esse ponto
}

/* void	alloc_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i] = ft_calloc(1, sizeof(t_texture));
		check_mem(game, &(game->mem_alloc.ptr_mem_list), \
			game->textures[i], "ft_calloc failed");
		i++;
	}
} */

void	init_textures(t_game *game)
{
	ft_printf(1, "		Initializing textures\n");
	// alloc_textures(game);
	game->textures[NO].img = xpm_to_image(game, game->map->no_texture);
	game->textures[NO].pixel_address = \
		mlx_get_data_addr(game->textures[NO].img, \
		&(game->textures[NO].bpp), &(game->textures[NO].size_line), \
		&(game->textures[NO].endian));
	game->textures[SO].img = xpm_to_image(game, game->map->so_texture);
	game->textures[SO].pixel_address = \
		mlx_get_data_addr(game->textures[SO].img, \
		&(game->textures[SO].bpp), &(game->textures[SO].size_line), \
		&(game->textures[SO].endian));
	game->textures[EA].img = xpm_to_image(game, game->map->ea_texture);
	game->textures[EA].pixel_address = \
		mlx_get_data_addr(game->textures[EA].img, \
		&(game->textures[EA].bpp), &(game->textures[EA].size_line), \
		&(game->textures[EA].endian));
	game->textures[WE].img = xpm_to_image(game, game->map->we_texture);
	game->textures[WE].pixel_address = \
		mlx_get_data_addr(game->textures[WE].img, \
		&(game->textures[WE].bpp), &(game->textures[WE].size_line), \
		&(game->textures[WE].endian));
	game->gun.img = xpm_to_image(game, "textures/GLOCK_0001.xpm");
	game->gun.pixel_address = \
		mlx_get_data_addr(game->gun.img, \
		&(game->gun.bpp), &(game->gun.size_line), \
		&(game->gun.endian));
	if (game->textures[NO].img == NULL || game->textures[SO].img == NULL \
		|| game->textures[EA].img == NULL || game->textures[WE].img == NULL)
	destroy_free_exit_error(game, "mlx_xpm_file_to_image failed");
}

void	init_game(t_game *game)
{
	ft_printf(1, "		Initializing functions game\n");
	init_variables_game(game);
	init_mlx(game);
	init_textures(game);
	init_raycasting(game);
}

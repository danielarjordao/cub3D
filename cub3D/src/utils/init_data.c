#include "../../includes/cub3d.h"

bool	init_map(t_map **map)
{
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
	(*map)->player_x = 0;
	(*map)->player_y = 0;
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
	game->mlx->connection = NULL;
	game->mlx->win = NULL;
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
	//game->img_grass = NULL;
}

void	init_textures(t_game *game)
{
	ft_printf(1, "		Initializing textures\n");
	(void)game;
	/* game->img_enemy2 = xpm_to_image(game, "./images/bat2.xpm");
	if (game->img_player_l == NULL || game->img_player_r == NULL
	|| game->img_grass == NULL || game->img_tree == NULL
	|| game->img_collectible == NULL || game->img_player_d == NULL
	|| game->img_player_u == NULL || game->img_dead1 == NULL
	|| game->img_dead2 == NULL || game->img_enemy1 == NULL
	|| game->img_enemy2 == NULL || game->img_player_exit == NULL
	|| game->img_exit == NULL)
	destroy_free_exit_error(game, \
	"mlx_xpm_file_to_image() in init_images failed"); */
}

void	init_raycasting(t_game *game)
{
	ft_printf(1, "		Initializing raycasting\n");
	(void)game;
}

void	init_game(t_game *game)
{
	ft_printf(1, "		Initializing functions game\n");
	init_variables_game(game);
	init_mlx(game);
	init_textures(game);
	init_raycasting(game);
}

# include "../../includes/cub3d.h"

void	start_game(t_game *game)
{
	ft_printf(1, "Initializing structures\n");
	init_game(game);
	ft_printf(1, "Structures initialized\n\n");
	raycasting();
	handle_events();
	ft_printf(1, "Starting game loop\n\n");
	mlx_loop(game->mlx->connection);
}

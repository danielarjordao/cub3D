#include "../../includes/cub3d.h"

void	start_game(void)
{
	ft_printf(1, "Initializing structures\n");
	init_mlx();
	init_textures();
	init_raycasting();
	ft_printf(1, "Structures initialized\n\n");
	raycasting();
	handle_events();
	ft_printf(1, "Starting game loop\n\n");
}

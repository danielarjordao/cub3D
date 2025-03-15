#include "../../includes/cub3d.h"

void	set_camera_plane(t_game *game)
{
	game->map->camera_x = game->map->player_dir_y * CAMERA_MAGNITUDE;
	game->map->camera_y = (-1) * game->map->player_dir_x * CAMERA_MAGNITUDE;
}

void	raycasting(t_game *game)
{
	ft_printf(1, "Starting raycasting\n");
	ft_printf(1, "		Save player position and direction\n");
	set_camera_plane(game);
	ft_printf(1, "		Calculate ray direction\n");
	ft_printf(1, "		Use DDA algorithm\n");
	ft_printf(1, "		Calculate ray distance\n");
	ft_printf(1, "		Calculate wall height\n");
	ft_printf(1, "Raycasting complete\n\n");
	render(game);
}

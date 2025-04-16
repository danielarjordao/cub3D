#include "../../includes/cub3d.h"

void	set_player_dir(t_game *game, double new_dir_x, double new_dir_y)
{
	double	magnitude;

	// Normalizar o vetor de direção
	magnitude = sqrt(new_dir_x * new_dir_x + new_dir_y * new_dir_y);
	game->map->player_dir_x = new_dir_x / magnitude;
	game->map->player_dir_y = new_dir_y / magnitude;
}

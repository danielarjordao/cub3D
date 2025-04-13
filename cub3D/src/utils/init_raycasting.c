#include "../../includes/cub3d.h"

void	init_player_direction(t_game *game)
{
	if (game->map->player_dir == 'N')
	{
		game->map->player_dir_x = 0.0;
		game->map->player_dir_y = -1.0;
	}
	else if (game->map->player_dir == 'W')
	{
		game->map->player_dir_x = -1.0;
		game->map->player_dir_y = 0.0;
	}
	else if (game->map->player_dir == 'S')
	{
		game->map->player_dir_x = 0.0;
		game->map->player_dir_y = 1.0;
	}
	else if (game->map->player_dir == 'E')
	{
		game->map->player_dir_x = 1.0;
		game->map->player_dir_y = 0.0;
	}
}

void	init_player_position(t_game *game)
{
	game->map->player_x += 0.5;
	game->map->player_y += 0.5;
}

void	init_raycasting(t_game *game)
{
	ft_printf(1, "		Initializing raycasting\n");
	ft_printf(1, "			Setting player view direction, %c\n", game->map->player_dir);
	init_player_direction(game);
	printf("			x = %f, y = %f\n", game->map->player_dir_x, game->map->player_dir_y);
	ft_printf(1, "			Setting player position\n");
	init_player_position(game);
	printf("			pos_x = %f\n", game->map->player_x);
	printf("			pos_y = %f\n", game->map->player_y);
}

#include "../../includes/cub3d.h"
#include <X11/keysym.h>

void	change_player_position(t_game *game, int key_code)
{
	double new_pos_x;
	double new_pos_y;

	if (key_code == XK_w)
	{
		new_pos_x = game->map->player_x + (0.1 * game->map->player_dir_x) / sqrt(game->map->player_dir_x * game->map->player_dir_x + game->map->player_dir_y * game->map->player_dir_y);
		new_pos_y = game->map->player_y + (0.1 * game->map->player_dir_y) / sqrt(game->map->player_dir_x * game->map->player_dir_x + game->map->player_dir_y * game->map->player_dir_y);
	}
	if (game->map->map[(int)new_pos_y][(int)new_pos_x] != 1)
	{
		game->map->player_x = new_pos_x;
		game->map->player_y = new_pos_y;
	}
}

void	move_player(t_game *game, int key_code)
{
	printf("Move_player function");
	if (key_code == XK_w)
		change_player_position(game, key_code);
	raycasting(game);
	printf("Player moved, the new pos_x is %f and pos_y is %f", game->map->player_x, game->map->player_y);
}

int	handle_key(int key_code, void *param)
{
	t_game *game;

	printf("Handle_key function %d e %d", key_code, XK_w);
	game = (t_game *)param;
	if (key_code == XK_Escape)
		close_game(game);
	if (key_code == XK_w || key_code == XK_S || key_code == XK_D || key_code == XK_A)
		move_player(game, key_code);
	return(EXIT_SUCCESS);
}

void	handle_events(t_game *game)
{
	ft_printf(1, "Handling events\n\n");
	mlx_hook(game->mlx->win, 17, (1L<<17), close_game, game);
	mlx_key_hook(game->mlx->win, handle_key, game);
}

#include "../../includes/cub3d.h"
#include <X11/keysym.h>

void	change_player_position(t_game *game)
{
	double new_pos_x;
	double new_pos_y;
	double dir_magnitude;

	dir_magnitude = sqrt(game->map->player_dir_x * game->map->player_dir_x + game->map->player_dir_y * game->map->player_dir_y);
	if (game->key_w == TRUE && game->key_s == FALSE)
	{
		new_pos_x = game->map->player_x + (DELTA_MOV * game->map->player_dir_x) / dir_magnitude;
		new_pos_y = game->map->player_y + (DELTA_MOV * game->map->player_dir_y) / dir_magnitude;
	}
	else if (game->key_w == FALSE && game->key_s == TRUE)
	{
		new_pos_x = game->map->player_x - (DELTA_MOV * game->map->player_dir_x) / dir_magnitude;
		new_pos_y = game->map->player_y - (DELTA_MOV * game->map->player_dir_y) / dir_magnitude;
	}
	if (game->key_a == TRUE && game->key_d == FALSE)
	{
		new_pos_x = game->map->player_x + (DELTA_MOV * game->map->player_dir_y) / dir_magnitude;
		new_pos_y = game->map->player_y + (DELTA_MOV * game->map->player_dir_x * (-1)) / dir_magnitude;
	}
	else if (game->key_a == FALSE && game->key_d == TRUE)
	{
		new_pos_x = game->map->player_x + (DELTA_MOV * game->map->player_dir_y * (-1)) / dir_magnitude;
		new_pos_y = game->map->player_y + (DELTA_MOV * game->map->player_dir_x) / dir_magnitude;
	}
	if (game->map->map[(int)new_pos_y][(int)new_pos_x] != 1)
	{
		game->map->player_x = new_pos_x;
		game->map->player_y = new_pos_y;
	}
	printf("Player moved, the new pos_x is %f and pos_y is %f\n", game->map->player_x, game->map->player_y);
}

void	rotate_player(t_game *game)
{
	printf("Move_player function");
	double radianos;

	radianos = ROTATE_ANGLE * M_PI / 180.0;
	if (game->key_left_arrow == TRUE && game->key_right_arrow == FALSE)
	{
		game->map->player_dir_x = cos(radianos) * game->map->player_dir_x - sin(radianos) * game->map->player_dir_y;
		game->map->player_dir_y = sin(radianos) * game->map->player_dir_x + cos(radianos) * game->map->player_dir_y;
	}
	else if (game->key_left_arrow == FALSE && game->key_right_arrow == TRUE)
	{
		game->map->player_dir_x = cos(-radianos) * game->map->player_dir_x - sin(-radianos) * game->map->player_dir_y;
		game->map->player_dir_y = sin(-radianos) * game->map->player_dir_x + cos(-radianos) * game->map->player_dir_y;
	}
}

int	handle_key(int key_code, void *param)
{
	t_game *game;

	printf("Handle_key function %d\n", key_code);
	game = (t_game *)param;
	if (key_code == XK_w)
		game->key_w = TRUE;
	else if (key_code == XK_a)
		game->key_a = TRUE;
	else if (key_code == XK_s)
		game->key_s = TRUE;
	else if (key_code == XK_d)
		game->key_d = TRUE;
	else if (key_code == XK_Left)
		game->key_left_arrow = TRUE;
	else if (key_code == XK_Right)
		game->key_right_arrow = TRUE;
	else if (key_code == XK_Escape)
		close_game(game);
	return(EXIT_SUCCESS);
}

int	handle_pressed_key(void *param)
{
	t_game *game;
	static int	count;
	bool	refresh;

	count++;
	if (count != 10000)
		return(EXIT_SUCCESS);
	refresh = FALSE;
	printf("handle_pressed_key function\n");
	game = (t_game *)param;
	if (game->key_w == TRUE || game->key_a == TRUE || game->key_s == TRUE || game->key_d == TRUE)
	{
		change_player_position(game);
		refresh = TRUE;
	}
	else if (game->key_left_arrow == TRUE  || game->key_right_arrow == TRUE )
	{
		rotate_player(game);
		refresh = TRUE;
	}	
	count = 0;
	if (refresh == TRUE)
		raycasting(game);
	return(EXIT_SUCCESS);
}
int	handle_keyrelease(int key_code, void *param)
{
	t_game *game;

	printf("handle_keyrelease function %d\n", key_code);
	game = (t_game *)param;
	if (key_code == XK_w)
		game->key_w = FALSE;
	else if (key_code == XK_a)
		game->key_a = FALSE;
	else if (key_code == XK_s)
		game->key_s = FALSE;
	else if (key_code == XK_d)
		game->key_d = FALSE;
	else if (key_code == XK_Left)
		game->key_left_arrow = FALSE;
	else if (key_code == XK_Right)
		game->key_right_arrow = FALSE;
	return(EXIT_SUCCESS);
}


void	handle_events(t_game *game)
{
	ft_printf(1, "Handling events\n\n");
	mlx_hook(game->mlx->win, 17, (1L<<17), close_game, game);
	mlx_hook(game->mlx->win, 2, (1L<<0), handle_key, game);
	mlx_hook(game->mlx->win, 3, (1L<<1), handle_keyrelease, game);
	mlx_loop_hook(game->mlx->connection, handle_pressed_key, game);
}

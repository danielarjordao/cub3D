#include "../../includes/cub3d.h"

void	set_delta_mov(t_game *game, double *delta_mov_x, \
	double *delta_mov_y)
{
	double	dir_magnitude;

	dir_magnitude = sqrt(pow(game->map->player_dir_x, 2) + \
		pow(game->map->player_dir_y, 2));
	if (game->key_w == TRUE && game->key_s == FALSE)
	{
		*delta_mov_x = (DELTA_MOV * game->map->player_dir_x) / dir_magnitude;
		*delta_mov_y = (DELTA_MOV * game->map->player_dir_y) / dir_magnitude;
	}
	else if (game->key_w == FALSE && game->key_s == TRUE)
	{
		*delta_mov_x = - (DELTA_MOV * game->map->player_dir_x) / dir_magnitude;
		*delta_mov_y = - (DELTA_MOV * game->map->player_dir_y) / dir_magnitude;
	}
	if (game->key_a == TRUE && game->key_d == FALSE)
	{
		*delta_mov_x += (DELTA_MOV * game->map->player_dir_y) / dir_magnitude;
		*delta_mov_y -= DELTA_MOV * game->map->player_dir_x / dir_magnitude;
	}
	else if (game->key_a == FALSE && game->key_d == TRUE)
	{
		*delta_mov_x -= DELTA_MOV * game->map->player_dir_y / dir_magnitude;
		*delta_mov_y += (DELTA_MOV * game->map->player_dir_x) / dir_magnitude;
	}
}

bool	check_moviment_path(t_game *game, int new_pos_x, int new_pos_y)
{
	if (new_pos_x != game->map->player_x && new_pos_y != game->map->player_y)
	{
		if (game->map->map[new_pos_y][(int)game->map->player_x] == '1')
			return (FALSE);
		if (game->map->map[(int)game->map->player_y][new_pos_x] == '1')
			return (FALSE);
	}
	if (game->map->map[(int)new_pos_y][(int)new_pos_x] == '1')
		return (FALSE);
	return (TRUE);
}

void	change_player_position(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;
	double	delta_mov_x;
	double	delta_mov_y;

	delta_mov_x = 0.0;
	delta_mov_y = 0.0;
	set_delta_mov(game, &delta_mov_x, &delta_mov_y);
	new_pos_x = game->map->player_x + 1.1 * delta_mov_x;
	new_pos_y = game->map->player_y + 1.1 * delta_mov_y;
	if (check_moviment_path(game, (int)new_pos_x, (int)new_pos_y))
	{
		game->map->player_x = new_pos_x;
		game->map->player_y = new_pos_y;
	}
	printf("Player moved, the new pos_x is %f and pos_y is %f\n", game->map->player_x, game->map->player_y);
}

void	rotate_player(t_game *game)
{
	double	radianos;
	double	magnitude;
	double	new_dir_x;
	double	new_dir_y;

	printf("Move_player function");
	radianos = ROTATE_ANGLE * M_PI / 180.0;
	if (game->key_left_arrow == FALSE && game->key_right_arrow == TRUE)
	{
		new_dir_x = cos(radianos) * game->map->player_dir_x - \
			sin(radianos) * game->map->player_dir_y;
		new_dir_y = sin(radianos) * game->map->player_dir_x + \
			cos(radianos) * game->map->player_dir_y;
	}
	else if (game->key_left_arrow == TRUE && game->key_right_arrow == FALSE)
	{
		new_dir_x = cos(-radianos) * game->map->player_dir_x - \
			sin(-radianos) * game->map->player_dir_y;
		new_dir_y = sin(-radianos) * game->map->player_dir_x + \
			cos(-radianos) * game->map->player_dir_y;
	}
	else
		return ;
	// Normalizar o vetor de direção
	magnitude = sqrt(new_dir_x * new_dir_x + new_dir_y * new_dir_y);
	game->map->player_dir_x = new_dir_x / magnitude;
	game->map->player_dir_y = new_dir_y / magnitude;
}

void	shooting(t_game *game, bool *refresh)
{
	static int	count_gun;

	if (count_gun == 0)
		*refresh = TRUE;
	count_gun++;
	if (count_gun == 4)
	{
		game->shooting = FALSE;
		count_gun = 0;
		*refresh = TRUE;
	}
}
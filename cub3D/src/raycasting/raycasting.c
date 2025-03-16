#include "../../includes/cub3d.h"

void	set_camera_plane(t_game *game)
{
	game->map->camera_x = game->map->player_dir_y * CAMERA_MAGNITUDE;
	game->map->camera_y = (-1) * game->map->player_dir_x * CAMERA_MAGNITUDE;
}

void	calculate_ray_dir(t_game *game, int x, float *ray_dir_x, float *ray_dir_y)
{
	int	fator;

	fator = ((2.0 * x) /  SCREEN_WIDTH) - 1;
	*ray_dir_x = game->map->camera_x * fator + game->map->player_dir_x;
	*ray_dir_y = game->map->camera_y * fator + game->map->player_dir_y;
}

void	casting_each_ray(t_game *game, int x)
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	ray_distance_to_cross_x;
	float	ray_distance_to_cross_y;
	float	player_x_distance_to_x_grid;
	float	player_y_distance_to_y_grid;

	calculate_ray_dir(game, x, &ray_dir_x, &ray_dir_y);

	//CALCULAR DISTANCIA PARA CRUZAR UMA UNIDADE DO EIXO X E Y
	if (ray_dir_x == 0)
		ray_distance_to_cross_x = INT_MAX;
	else
		ray_distance_to_cross_x = abs(1 / game->map->player_dir_x);
	if (ray_dir_y == 0)
		ray_distance_to_cross_y = INT_MAX;
	else
		ray_distance_to_cross_y = abs(1 / game->map->player_dir_y);
	
	//PEGAR DIRECAO DO RAIO E DIRECAO DO PLAYER PARA A LINHA DO GRID DO EIXO X E Y
	if (ray_dir_x < 0)
	{
		game->map->ray_x_direction = -1;
		player_x_distance_to_x_grid = (game->map->player_x - (int)game->map->player_x) * ray_distance_to_cross_x;
	}
	else
	{
		game->map->ray_x_direction = 1;
		player_y_distance_to_y_grid = ((int)game->map->player_x + 1.0 - game->map->player_x) * ray_distance_to_cross_x;
	}
	if (ray_dir_x < 0)
	{
		game->map->ray_y_direction = -1;
		player_x_distance_to_x_grid = (game->map->player_y - (int)game->map->player_y) * ray_distance_to_cross_y;
	}
	else
	{
		game->map->ray_y_direction = 1;
		player_y_distance_to_y_grid = ((int)game->map->player_y + 1.0 - game->map->player_y) * ray_distance_to_cross_y;
	}
}

void	raycasting(t_game *game)
{
	ft_printf(1, "Starting raycasting\n");
	ft_printf(1, "		Save player position and direction\n");
	set_camera_plane(game);
	ft_printf(1, "		Calculate ray direction\n");
	int	x;
	float	ray_dir_x;
	float	ray_dir_y;
	float	ray_distance_to_cross_x;
	float	ray_distance_to_cross_y;
	float	player_x_distance_to_x_grid;
	float	player_y_distance_to_y_grid;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		casting_each_ray(game, x);	
	}
	ft_printf(1, "		Use DDA algorithm\n");
	ft_printf(1, "		Calculate ray distance\n");
	ft_printf(1, "		Calculate wall height\n");
	ft_printf(1, "Raycasting complete\n\n");
	render(game);
}

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
	int	step_x;
	int	step_y;
	int	ray_x_grid;
	int	ray_y_grid;
	float	player_x_distance_to_x_grid;
	float	player_y_distance_to_y_grid;

	//PEGAR O QUADRANTE QUE O RAIO SE ENCONTRA
	ray_x_grid = (int)game->map->player_x;
	ray_y_grid = (int)game->map->player_y;

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
	
	printf("Distancia percorrida para atravessar uma unidade do eixo x: %f\n", ray_distance_to_cross_x);
	printf("Distancia percorrida para atravessar uma unidade do eixo y: %f\n", ray_distance_to_cross_y);
	

	//PEGAR DIRECAO DO RAIO E DIRECAO DO PLAYER PARA A LINHA DO GRID DO EIXO X E Y
	//REVIEW -> e se a distancia der 0? transformo em 1?
	if (ray_dir_x < 0)
	{
		step_x = -1;
		player_x_distance_to_x_grid = (game->map->player_x - ray_x_grid) * ray_distance_to_cross_x;
	}
	else
	{
		step_x = 1;
		player_x_distance_to_x_grid = (ray_x_grid + 1.0 - game->map->player_x) * ray_distance_to_cross_x;
	}
	if (!player_x_distance_to_x_grid)
		player_x_distance_to_x_grid = 1.0;
	printf("Direcao do raio x: %d",step_x);
	printf("Distância do player para o grid x: %f", player_x_distance_to_x_grid);
	if (ray_dir_y < 0)
	{
		step_y = -1;
		player_y_distance_to_y_grid = (game->map->player_y - ray_y_grid) * ray_distance_to_cross_y;
	}
	else
	{
		step_y = 1;
		player_y_distance_to_y_grid = (ray_y_grid + 1.0 - game->map->player_y) * ray_distance_to_cross_y;
	}
	if (!player_y_distance_to_y_grid)
			player_y_distance_to_y_grid = 1.0;
	printf("Direcao do raio x: %d",step_y);
	printf("Distância do player para o grid x: %f", player_y_distance_to_y_grid);

	//Incrementar raio ate bater em uma parede
	float	ray_x;
	float	ray_y;

	ray_x = game->map->player_x;
	ray_y = game->map->player_y;
	while (!is_wall((int)ray_x, (int)ray_y))
	{
		if (player_x_distance_to_x_grid < player_y_distance_to_y_grid)
		{
			ray_x += game->map->player_dir_x * player_x_distance_to_x_grid;
			ray_y += game->map->player_dir_y * player_x_distance_to_x_grid;
		}
		else
		{
			ray_x += game->map->player_dir_x * player_y_distance_to_y_grid;
			ray_y += game->map->player_dir_y * player_y_distance_to_y_grid;
		}
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

#include "../../includes/cub3d.h"

void	set_camera_plane(t_game *game)
{
	game->map->camera_x = game->map->player_dir_y * CAMERA_MAGNITUDE;
	game->map->camera_y = (-1) * game->map->player_dir_x * CAMERA_MAGNITUDE;
}

//Calculamos O fator que vai de -1 a 1 e nos dá em qual parte do plano da camera o raio está
void	calculate_ray_dir(t_game *game, int x_screen)
{
	int	fator;

	fator = ((2.0 * x_screen) /  SCREEN_WIDTH) - 1;
	game->ray.dir_x = game->map->camera_x * fator + game->map->player_dir_x;
	game->ray.dir_y = game->map->camera_y * fator + game->map->player_dir_y;
}

void	casting_each_ray(t_game *game, int x_screen)
{
	//PEGAR O QUADRANTE QUE O RAIO SE ENCONTRA
	game->ray.x_grid = (int)game->map->player_x;
	game->ray.y_grid = (int)game->map->player_y;

	calculate_ray_dir(game, x_screen);

	//CALCULAR DISTANCIA PARA CRUZAR UMA UNIDADE DO EIXO X E Y
	if (game->ray.dir_x == 0)
		game->ray.length_per_x_unity = INT_MAX;
	else
		game->ray.length_per_x_unity = abs(1 / game->ray.dir_x);
	if (game->ray.dir_y == 0)
		game->ray.length_per_y_unity = INT_MAX;
	else
		game->ray.length_per_y_unity = abs(1 / game->ray.dir_y);
	printf("Distancia percorrida para atravessar uma unidade do eixo x: %f\n", game->ray.length_per_x_unity);
	printf("Distancia percorrida para atravessar uma unidade do eixo y: %f\n", game->ray.length_per_y_unity);
	

	//PEGAR DIRECAO DO RAIO E DIRECAO DO PLAYER PARA A LINHA DO GRID DO EIXO X E Y
	//REVIEW -> e se a distancia der 0? transformo em 1?
	if (game->ray.dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.magnitude_crossing_x = (game->map->player_x - game->ray.x_grid) * game->ray.length_per_x_unity;
	}
	else if (game->ray.dir_x > 0)
	{
		game->ray.step_x = 1;
		game->ray.magnitude_crossing_x = (game->ray.x_grid + 1.0 - game->map->player_x) * game->ray.length_per_x_unity;
	}
	else
		game->ray.magnitude_crossing_x = INT_MAX;
	printf("Direcao do raio x: %d", game->ray.step_x);
	printf("Distância do player para o grid x: %f", game->ray.magnitude_crossing_x);
	if (game->ray.dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.magnitude_crossing_y = (game->map->player_y - game->ray.y_grid) * game->ray.length_per_y_unity;
	}
	else if (game->ray.dir_y > 0)
	{
		game->ray.step_y = 1;
		game->ray.magnitude_crossing_y = (game->ray.y_grid + 1.0 - game->map->player_y) * game->ray.length_per_y_unity;
	}
	else
		game->ray.magnitude_crossing_y = INT_MAX;
	printf("Direcao do raio x: %d",game->ray.step_y);
	printf("Distância do player para o grid x: %f", game->ray.magnitude_crossing_y);

	//Incrementar raio ate bater em uma parede
	ft_printf(1, "		Use DDA algorithm\n");
	int	hit_grid;
	int	perpWallDist;

	game->ray.y_grid = game->map->player_y;
	hit_grid = NONE;
	while (hit_grid == NONE)
	{
		if (game->ray.magnitude_crossing_x < game->ray.magnitude_crossing_y)
		{
			game->ray.magnitude_crossing_x += game->ray.length_per_x_unity;
			game->ray.x_grid += game->ray.step_x;
			if (game->map->map[game->ray.y_grid][game->ray.x_grid] == '1')
					hit_grid = VERTICAL;
		}
		else
		{
			game->ray.magnitude_crossing_y += game->ray.length_per_y_unity;
			game->ray.y_grid += game->ray.step_y;
			if (game->map->map[game->ray.y_grid][game->ray.x_grid] == '1')
					hit_grid = HORIZONTAL;
		}
	}
	ft_printf(1, "		Calculate ray distance\n");
	if (hit_grid == VERTICAL)
		perpWallDist = (game->ray.magnitude_crossing_x - game->ray.length_per_x_unity);
	else
      		perpWallDist = (game->ray.magnitude_crossing_y - game->ray.length_per_y_unity);
	ft_printf(1, "		Calculate wall height\n");
	int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
	ft_printf(1, "Raycasting complete\n\n");
}

void	raycasting(t_game *game)
{
	ft_printf(1, "Starting raycasting\n");
	ft_printf(1, "		Save player position and direction\n");
	set_camera_plane(game);
	ft_printf(1, "		Calculate ray direction\n");
	int	x_screen;

	x_screen = 0;
	while (x_screen < SCREEN_WIDTH)
	{
		casting_each_ray(game, x_screen);
		render(game, x_screen, game->ray.wall_height);
		x_screen++;	
	}
	mlx_put_image_to_window(game->mlx->connection, game->mlx->win, game->mlx->img_to_render, 0 , 0);
}

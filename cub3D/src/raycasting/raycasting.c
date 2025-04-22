/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:46:12 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:51:12 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_camera_plane(t_game *game)
{
	game->map->camera_x = (-1) * game->map->player_dir_y * CAMERA_MAGNITUDE;
	game->map->camera_y = game->map->player_dir_x * CAMERA_MAGNITUDE;
}

//Calculamos O fator que vai de -1 a 1 e
//nos dá em qual parte do plano da camera o raio está
void	calculate_ray_dir(t_game *game, int x_screen)
{
	double	fator;

	fator = ((2.0 * x_screen) / SCREEN_WIDTH) - 1;
	game->ray.dir_x = game->map->camera_x * fator + game->map->player_dir_x;
	game->ray.dir_y = game->map->camera_y * fator + game->map->player_dir_y;
}

void	calculate_length_per_unity(t_game *game)
{
	if (game->ray.dir_x == 0)
		game->ray.length_per_x_unity = INT_MAX;
	else
		game->ray.length_per_x_unity = fabs(1 / game->ray.dir_x);
	if (game->ray.dir_y == 0)
		game->ray.length_per_y_unity = INT_MAX;
	else
		game->ray.length_per_y_unity = fabs(1 / game->ray.dir_y);
}

void	casting_each_ray(t_game *game, int x_screen)
{
	game->ray.x_grid = (int)game->map->player_x;
	game->ray.y_grid = (int)game->map->player_y;
	calculate_ray_dir(game, x_screen);
	calculate_length_per_unity(game);
	calculate_magnitute_crossing_axis(game);
	check_hit_grid(game);
	if (game->ray.hit_grid == VERTICAL)
		game->ray.perp_wall_dist = \
			(game->ray.magnitude_crossing_x - game->ray.length_per_x_unity);
	else
		game->ray.perp_wall_dist = \
			(game->ray.magnitude_crossing_y - game->ray.length_per_y_unity);
	game->ray.wall_height = (int)(SCREEN_HEIGHT / game->ray.perp_wall_dist);
}

void	raycasting(t_game *game)
{
	int	x_screen;

	set_camera_plane(game);
	x_screen = 0;
	while (x_screen < SCREEN_WIDTH)
	{
		casting_each_ray(game, x_screen);
		render(game, x_screen, game->ray.wall_height);
		x_screen++;
	}
	mlx_mouse_move(game->mlx->connection, game->mlx->win, \
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_put_image_to_window(game->mlx->connection, \
		game->mlx->win, game->mlx->img_to_render, 0, 0);
}

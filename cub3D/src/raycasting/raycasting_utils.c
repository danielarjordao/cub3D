/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:46:06 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:46:07 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_magnitute_crossing_x(t_game *game)
{
	if (game->ray.dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.magnitude_crossing_x = \
			(game->map->player_x - game->ray.x_grid) * \
			game->ray.length_per_x_unity;
	}
	else if (game->ray.dir_x > 0)
	{
		game->ray.step_x = 1;
		game->ray.magnitude_crossing_x = \
			(game->ray.x_grid + 1.0 - game->map->player_x) * \
			game->ray.length_per_x_unity;
	}
	else
		game->ray.magnitude_crossing_x = INT_MAX;
}

void	calculate_magnitute_crossing_y(t_game *game)
{
	if (game->ray.dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.magnitude_crossing_y = \
			(game->map->player_y - game->ray.y_grid) * \
			game->ray.length_per_y_unity;
	}
	else if (game->ray.dir_y > 0)
	{
		game->ray.step_y = 1;
		game->ray.magnitude_crossing_y = \
			(game->ray.y_grid + 1.0 - game->map->player_y) * \
			game->ray.length_per_y_unity;
	}
	else
		game->ray.magnitude_crossing_y = INT_MAX;
}

void	calculate_magnitute_crossing_axis(t_game *game)
{
	calculate_magnitute_crossing_x(game);
	calculate_magnitute_crossing_y(game);
}

void	check_hit_grid(t_game *game)
{
	game->ray.hit_grid = NONE;
	while (game->ray.hit_grid == NONE)
	{
		if (game->ray.magnitude_crossing_x < game->ray.magnitude_crossing_y)
		{
			game->ray.magnitude_crossing_x += game->ray.length_per_x_unity;
			game->ray.x_grid += game->ray.step_x;
			if (game->map->map[game->ray.y_grid][game->ray.x_grid] == '1')
				game->ray.hit_grid = VERTICAL;
		}
		else
		{
			game->ray.magnitude_crossing_y += game->ray.length_per_y_unity;
			game->ray.y_grid += game->ray.step_y;
			if (game->map->map[game->ray.y_grid][game->ray.x_grid] == '1')
				game->ray.hit_grid = HORIZONTAL;
		}
	}
}

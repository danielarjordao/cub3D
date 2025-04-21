/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:46:47 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:46:48 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	init_player_direction(game);
	init_player_position(game);
}

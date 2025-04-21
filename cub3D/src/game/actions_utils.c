/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:45:44 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:45:45 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_player_dir(t_game *game, double new_dir_x, double new_dir_y)
{
	double	magnitude;

	// Normalizar o vetor de direção
	magnitude = sqrt(new_dir_x * new_dir_x + new_dir_y * new_dir_y);
	game->map->player_dir_x = new_dir_x / magnitude;
	game->map->player_dir_y = new_dir_y / magnitude;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:36:59 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:37:00 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	start_game(t_game *game)
{
	init_game(game);
	raycasting(game);
	handle_events(game);
	mlx_loop(game->mlx->connection);
}

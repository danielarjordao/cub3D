/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:45:55 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:45:56 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mouse_hook(int x, int y, t_game *game)
{
	(void)y;
	game->delta_x_mouse = x - SCREEN_WIDTH / 2;
	return (EXIT_SUCCESS);
}

int	handle_mouse_click(int button, int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	(void) x;
	(void) y;
	if (button == Button1)
		game->shooting = TRUE;
	return (EXIT_SUCCESS);
}

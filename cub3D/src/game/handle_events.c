/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:45:51 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:45:52 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_key(int key_code, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key_code == XK_w)
		game->key_w = TRUE;
	else if (key_code == XK_a)
		game->key_a = TRUE;
	else if (key_code == XK_s)
		game->key_s = TRUE;
	else if (key_code == XK_d)
		game->key_d = TRUE;
	else if (key_code == XK_Left)
		game->key_left_arrow = TRUE;
	else if (key_code == XK_Right)
		game->key_right_arrow = TRUE;
	else if (key_code == XK_Escape)
		close_game(game);
	return (EXIT_SUCCESS);
}

int	handle_pressed_key(void *param)
{
	t_game		*game;
	static int	count;
	bool		refresh;

	if (++count != 7000)
		return (EXIT_SUCCESS);
	refresh = FALSE;
	game = (t_game *)param;
	if (game->key_w == TRUE || game->key_a == TRUE \
		|| game->key_s == TRUE || game->key_d == TRUE)
	{
		change_player_position(game);
		refresh = TRUE;
	}
	if (game->key_left_arrow == TRUE || game->key_right_arrow == TRUE \
		|| game->delta_x_mouse != 0)
	{
		rotate_player(game);
		refresh = TRUE;
	}
	if (game->shooting == TRUE)
		shooting(game, &refresh);
	if (refresh == TRUE)
		raycasting(game);
	return (count = 0, EXIT_SUCCESS);
}

int	handle_keyrelease(int key_code, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key_code == XK_w)
		game->key_w = FALSE;
	else if (key_code == XK_a)
		game->key_a = FALSE;
	else if (key_code == XK_s)
		game->key_s = FALSE;
	else if (key_code == XK_d)
		game->key_d = FALSE;
	else if (key_code == XK_Left)
		game->key_left_arrow = FALSE;
	else if (key_code == XK_Right)
		game->key_right_arrow = FALSE;
	return (EXIT_SUCCESS);
}

void	handle_events(t_game *game)
{
	mlx_hook(game->mlx->win, DestroyNotify, StructureNotifyMask, close_game, game);
	mlx_hook(game->mlx->win, KeyPress, KeyPressMask, handle_key, game);
	mlx_hook(game->mlx->win, KeyRelease, KeyReleaseMask, handle_keyrelease, game);
	mlx_hook(game->mlx->win, MotionNotify, PointerMotionMask, mouse_hook, game);
	mlx_mouse_hook(game->mlx->win, handle_mouse_click, game);
	mlx_loop_hook(game->mlx->connection, handle_pressed_key, game);
}
